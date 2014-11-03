#include "shader.hpp"
#include "../renderhelp.hpp"
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>

Shader& Shader::GetInstance(int x,int y,int s){
    static Shader teste(x,y,s);
    return teste;
}

Shader::Shader(int sx,int sy,int blockwh){
    sizeY = sy/blockwh;
    sizeX = sx/blockwh;
    blockSize = blockwh;
    PermissiveAmbient = 20.5;
    MaxCycles = 74;
    ShadeMap = new unsigned char*[sy/blockwh];
    DataMap = new unsigned char*[sy/blockwh];
    UseThreads =1;  //OMP
    UsePThreads=1;  //pthreads
    for (int y=0;y<sizeY;y++){
        ShadeMap[y] = new unsigned char[sx/blockwh];
        DataMap[y] = new unsigned char[sx/blockwh];

        for (int x=0;x<sizeX;x++){
            ShadeMap[y][x] = 255;
            DataMap[y][x] = 0;
        }
    }
    Maps  =     new unsigned char**[UseThreads];
    Mapsaux =   new unsigned char**[UseThreads];
    std::cout << "Creating!\n";
    for (int i=0;i<UseThreads;i++){

       Maps[i] = new unsigned char*[sizeY];

       for (int y=0;y<sizeY;y++){
            Maps[i][y]      = new unsigned char[sizeX];

            for (int x=0;x<sizeX;x++){
                Maps[i][y][x] = 255;
            }
       }

    }

    light = new Sprite("img/light.png");
    block = new Sprite("img/block.png");

}
Shader::~Shader(){
    for (int y=0;y<sizeY;y++){
        delete ShadeMap[y];
        delete DataMap[y];
    }

    delete light;
    delete block;
    delete ShadeMap;
    delete DataMap;
}

bool Shader::IsInLimits(int x,int y){
    if (x < 0 or x >= sizeX or y < 0 or y >= sizeY){
        return false;
    }
    return true;
}

void Shader::SetMaxCycles(int n){
    MaxCycles += n;
    MaxCycles = std::max(0,MaxCycles);
    MaxCycles = std::min(MaxCycles,255);
};
int  Shader::GetAround(unsigned char** map,int x,int y){

    int n = 0;
    int k = 0;

    for (int ay=-1;ay<=1;ay++){
         for (int ax=-1;ax<=1;ax++){
            if (IsInLimits(x+ax,y+ay)){
                n += map[y+ay][x+ax];
                k++;
            }
        }
    }
    return n/k;
}

void Shader::ClearLights(){
    for (int y=0;y<sizeY;y++){
        for (int x=0;x<sizeX;x++){
            if (DataMap[y][x] <= 126 and DataMap[y][x] != 0){
                DataMap[y][x] = 0;
            }
        }
    }
}
bool Shader::AddLight(int x,int y,unsigned char strenght){
    if (IsInLimits(x,y) && DataMap[y][x] == 0){
        DataMap[y][x] = (((strenght/2)) & 127) -1;
        return true;
    }
    return false;
}
void Shader::AddBlock(int x,int y,unsigned char strenght){
    if (IsInLimits(x,y) && DataMap[y][x] == 0){
        DataMap[y][x] = (((strenght/2)) & 127) + 126;
    }
}



void *parallellight__(void *vec){
    parameters PARAM = *((parameters*)vec);
    int dis = PARAM.dis;;
    int Threads = PARAM.Threads;
    unsigned char strenght = PARAM.strenght;
    int x = PARAM.x;
    int y = PARAM.y;
    Shader *MINE = PARAM.MINE;
    unsigned char ** ShadeMapAux = PARAM.ShadeMapAux;
    int MaxCycles = PARAM.MaxCycles;
    int i,max;

    i = dis * (MaxCycles/Threads);
    max = (dis+1) * (MaxCycles/Threads);

    for (;i<max;i++){
    //Paralelismo a esse nivel não vale a pena =/
    //for (int i=0;i<MaxCycles;i++){
        float STR = strenght*2;
        int lsx=0,lsy=0;
        for (int step=0;STR>0;step++){
            int sx = sin(i * (360/(float)MaxCycles) * M_PI / 180.0)*step;
            int sy = cos(i * (360/(float)MaxCycles) * M_PI / 180.0)*step;
            if (lsx == (int)sx and lsy == (int)sy)
                continue;
            lsx = sx;
            lsy = sy;
            if (MINE->IsInLimits(x+sx,y+sy)){
                if(ShadeMapAux[y+sy][x+sx] == 255 and MINE->DataMap[y][x] != 0 and MINE->DataMap[y+sy][x+sx] <= 126 ){ //fix
                //
                    unsigned char Lum = ShadeMapAux[y+sy][x+sx];
                    Lum = std::max(0,  (Lum)-(int)(STR));
                    ShadeMapAux[y+sy][x+sx] = Lum;
                }else if (MINE->DataMap[y+sy][x+sx] > 126){
                    unsigned char Lum = ShadeMapAux[y+sy][x+sx];
                    STR -= (255/MINE->DataMap[y+sy][x+sx]*STR);
                    Lum = std::max(0,  (Lum)-(int)(STR));
                    ShadeMapAux[y+sy][x+sx] = Lum;

                }
            }
            STR -= MINE->PermissiveAmbient;
        }
    }
    pthread_exit(NULL);
}


unsigned char** Shader::ShootLightRay(int x,int y,unsigned char strenght, unsigned char ** ShadeMapAux){
    unsigned char** VartoRet= new unsigned char*[sizeY];
    for (int y=0;y<sizeY;y++){
        VartoRet[y] = new unsigned char[sizeX];
        for (int x=0;x<sizeX;x++){
            ShadeMapAux[y][x] = 255;

            VartoRet[y][x] = 255;
        }
    }
    ShadeMapAux[y][x] = ShadeMapAux[y][x] - strenght*2;
    pthread_t *threads_;
    threads_ = new  pthread_t[UsePThreads];
    parameters *params = new parameters[UsePThreads];
    for (int i=0;i<UsePThreads;i++){
        params[i].dis = i;
        params[i].Threads = UsePThreads;
        params[i].strenght = strenght;
        params[i].y = y;
        params[i].x = x;
        params[i].MINE = this;
        params[i].ShadeMapAux = ShadeMapAux;
        params[i].MaxCycles = MaxCycles;
        pthread_create(&threads_[i], NULL, &parallellight__, &params[i]);
    }
    for (int i=0;i<UsePThreads;i++){
        pthread_join(threads_[i], NULL);
    }

    #pragma omp parallel num_threads(UseThreads)
    for (int y=0;y<sizeY;y++){
        for (int x=0;x<sizeX;x++){
            VartoRet[y][x] = GetAround(ShadeMapAux,x,y);
        }
    }
    delete threads_;
    delete params;
    return VartoRet;
}

void Shader::Update(float dt){

    std::stack<unsigned char**> LightSpots; //Not thread safe!
    //Busca
    #pragma omp parallel for num_threads(UseThreads)
    for (int y=0;y<sizeY;y++){
        for (int x=0;x<sizeX;x++){
            ShadeMap[y][x] = 255; //Reset old shade map
            if (DataMap[y][x] != 0 and DataMap[y][x] <= 126){ //fix
                //Disparar light!
                //#pragma omp nowait
                //{
                    unsigned char jaaj = DataMap[y][x];
                    unsigned char **Ret = ShootLightRay(x,y,jaaj,Maps[omp_get_thread_num()]);
                    #pragma omp critical
                    LightSpots.emplace(Ret);
                //}

            }
        }

    }
    while (LightSpots.size() > 0){
        unsigned char **Ret = LightSpots.top();
        LightSpots.pop();
        #pragma omp parallel for num_threads(UseThreads)
        for (int y=0;y<sizeY;y++){
           for (int x=0;x<sizeX;x++){
               unsigned char K = Ret[y][x];//GetAround(Ret,x,y); //Segundo borramento!
               if (ShadeMap[y][x] < 254){
                    int offset = 255-ShadeMap[y][x];
                    K = std::max(K-offset,0);
               }
            ShadeMap[y][x] = std::min(ShadeMap[y][x],K);

           }
        }
        for (int y=0;y<sizeY;y++){
            delete Ret[y];
        }
        delete Ret;
    }


}
void Shader::Render(){
    //Render is not threadsafe
    for (int y=0;y<sizeY;y++)
        for (int x=0;x<sizeX;x++){
            if (DataMap[y][x] != 0){
                if (DataMap[y][x] <= 126){
                    light->Render(blockSize*x,blockSize*y);
                    RenderHelp::DrawSquareColorA(blockSize*x,blockSize*y,blockSize,blockSize,255,255,0, 100 );
                }else{
                    block->Render(blockSize*x,blockSize*y);

                }
            }

        }

    for (int y=0;y<sizeY;y++)
        for (int x=0;x<sizeX;x++){
            //RenderHelp::DrawSquareColorA(blockSize*x,blockSize*y,blockSize,blockSize,0,0,0, ShadeMap[y][x] );
            RenderHelp::DrawSquareColorA(blockSize*x,blockSize*y,blockSize,blockSize,0,0,0, GetAround(ShadeMap,x,y) );
        }

}
