#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <sys/time.h>
#include <fstream>
#include <random>
#include <functional>



int threads=4,ompthreads=1;
int seed = -1;
long int tosses = 10000;
pthread_t *threads_;

struct timeval start, end;

typedef struct myParameter_{
    int inside;
    int toss;
    float ret;
    int mythread;
    unsigned int seed;
} myParameter;

myParameter *params;

void *genPI(void *param)
{
       std::uniform_int_distribution<int> raar(0, 10000000);
       std::mt19937 RRENG;
       auto dice_roller = std::bind(raar, RRENG);

       myParameter *P = (myParameter*)param;

       P->inside = 0;
       int test = 0;
       #pragma omp parallel for num_threads(ompthreads) reduction(+ : test)
        for (int i=0;i<P->toss;i++){
            float XX = dice_roller()/10000000.0;
            float YY = dice_roller()/10000000.0;
            if (XX*XX + YY*YY <= 1){
               test++;
            }
        }
        P->inside = test;

       pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    if (argc <= 1){
        return 0;
	}
	for (int i=0;i<argc;i++){
        if (argv[i][1] == 't'){
            sscanf(argv[i],"-t=%d",&threads);
        }
        if (argv[i][1] == 'p'){
            sscanf(argv[i],"-p=%d",&ompthreads);
        }
        if (argv[i][1] == 's'){
            sscanf(argv[i],"-s=%d",&seed);
        }
        if (argv[i][1] == 'c'){
            sscanf(argv[i],"-c=%ld",&tosses);
        }
	}


	gettimeofday(&start, NULL);
	threads_ = new  pthread_t[threads];
	params = new myParameter[threads];
	float *ret =new float[threads];
	if (seed == -1){
        seed = time(NULL);
	}
    for (int i = 0; i < threads; i++)
    {
        params[i].seed = seed + i;
        params[i].toss = tosses/(float)threads;
        params[i].mythread = i;
        pthread_create(&threads_[i], NULL, genPI, (void *) &params[i]);
    }
    for (int i = 0; i < threads; i++)
    {
        pthread_join(threads_[i], NULL);
    }
    int N = 0;

    for (int i = 0; i < threads; i++)
    {
        N += params[i].inside;
    }
    gettimeofday(&end, NULL);




    std::fstream file("static.txt", std::ios::out | std::ios::app);
    //
    double dur = (end.tv_sec - start.tv_sec) + ( (end.tv_usec - start.tv_usec )/100000000.0);

    std::cout << "Value of pi is around: " << ((double)N/(float)tosses)*4.0 << "\nFinished in " << dur <<"\n";
    file << "[" << seed << "," << tosses << "," << threads << ","  << ((double)N/(float)tosses)*4.0 << "=" << (double)dur << "]" << std::endl;
    //
    file.close();

    return 1;
}
