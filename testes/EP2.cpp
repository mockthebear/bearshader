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
pthread_barrier_t our_barrier;

pthread_mutex_t lock;
void *genPI(void *param)
{
       //pthread_barrier_wait(&our_barrier);

       myParameter *P = (myParameter*)param;
       pthread_mutex_lock(&lock);
       std::cout << "Hi tred" << P->mythread << "\n";
       pthread_mutex_unlock(&lock);


       pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    pthread_barrier_init(&our_barrier,NULL,4);
   if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

	gettimeofday(&start, NULL);
	threads = 4;
	threads_ = new  pthread_t[threads];
	params = new myParameter[threads];
	float *ret =new float[threads];
	if (seed == -1){
        seed = time(NULL);
	}
    for (int i = 0; i < threads; i++)
    {
        params[i].mythread = i;
        pthread_create(&threads_[i], NULL, genPI, (void *) &params[i]);
    }
    for (int i = 0; i < threads; i++)
    {
        pthread_join(threads_[i], NULL);
    }




    return 1;
}
