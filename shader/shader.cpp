#include "shader.hpp"
#include "../renderhelp.hpp"
#include <math.h>
#include <stdlib.h>
#include <omp.h>


Shader::Shader(int sx,int sy,int blockwh){
    sizeY = sy/blockwh;
    sizeX = sx/blockwh;
    blockSize = blockwh;
    PermissiveAmbient = 55.5;
    MaxCycles = 74;
    ShadeMap = new unsigned char*[sy/blockwh];
    DataMap = new unsigned char*[sy/blockwh];
    UseThreads = 32;
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
       Mapsaux[i] = new unsigned char*[sizeY];
       for (int y=0;y<sizeY;y++){
            Maps[i][y]      = new unsigned char[sizeX];
            Mapsaux[i][y]   = new unsigned char[sizeX];
            for (int x=0;x<sizeX;x++){
                Maps[i][y][x] = 255;
                Mapsaux[i][y][x] = 255;
            }
       }

    }

}
Shader::~Shader(){
    for (int y=0;y<sizeY;y++){
        delete ShadeMap[y];
        delete DataMap[y];
    }

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

void Shader::AddLight(int x,int y,unsigned char strenght){
    if (IsInLimits(x,y)){
        DataMap[y][x] = (((strenght/2)) & 127) -1;
    }
}


unsigned char** Shader::ShootLightRay(int x,int y,unsigned char strenght, unsigned char ** ShadeMapAux, unsigned char **ShadeMapAux2){
    unsigned char** VartoRet= new unsigned char*[sizeY];
    for (int y=0;y<sizeY;y++){
        VartoRet[y] = new unsigned char[sizeX];
        for (int x=0;x<sizeX;x++){
            ShadeMapAux[y][x] = 255;
            ShadeMapAux2[y][x] = 255;
            VartoRet[y][x] = 255;
        }
    }
    ShadeMapAux[y][x] = ShadeMapAux[y][x] - strenght*2;
    for (int i=0;i<MaxCycles;i++){
       float STR = strenght*2;
       int lsx=0,lsy=0;
       for (int step=0;STR>0;step++){
            int sx = sin(i * (360/(float)MaxCycles) * M_PI / 180.0)*step;
            int sy = cos(i * (360/(float)MaxCycles) * M_PI / 180.0)*step;

            if (lsx == (int)sx and lsy == (int)sy)
                continue;
            lsx = sx;
            lsy = sy;

            if (IsInLimits(x+sx,y+sy)){
                if(ShadeMapAux[y+sy][x+sx] == 255 and DataMap[y+sy][x+sx] <= 126 ){ //fix
                //
                register unsigned char Lum = ShadeMapAux[y+sy][x+sx];
                Lum = std::max(0,  (Lum)-(int)(STR));
                ShadeMapAux[y+sy][x+sx] = Lum;
                }



           }
           STR -= PermissiveAmbient;


       }

    }
    for (int y=0;y<sizeY;y++){
        for (int x=0;x<sizeX;x++){
            VartoRet[y][x] = ShadeMapAux[y][x];//GetAround(ShadeMapAux,x,y);
        }
    }
    return VartoRet;

}

void Shader::Update(float dt){
    for (int y=0;y<sizeY;y++){
        for (int x=0;x<sizeX;x++){
            ShadeMap[y][x] = 255;
        }
    }
    std::stack<unsigned char**> LightSpots; //Not thread safe!

    #pragma omp parallel for num_threads(UseThreads)
    for (int y=0;y<sizeY;y++){
        for (int x=0;x<sizeX;x++){
            if (DataMap[y][x] != 0 and DataMap[y][x] <= 126){ //fix
                //Disparar light!
                #pragma omp nowait
                {
                    unsigned char jaaj = DataMap[y][x];
                    unsigned char **Ret = ShootLightRay(x,y,jaaj,Maps[omp_get_thread_num()],Mapsaux[omp_get_thread_num()]);
                    #pragma omp critical
                    LightSpots.emplace(Ret);
                }

            }
        }

    }

    while (LightSpots.size() > 0){
        unsigned char **Ret = LightSpots.top();
        LightSpots.pop();
        for (int y=0;y<sizeY;y++){
           for (int x=0;x<sizeX;x++){
               unsigned char K =  Ret[y][x];//GetAround(Ret,x,y); //Segundo borramento!
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
    for (int y=0;y<sizeY;y++)
        for (int x=0;x<sizeX;x++){
            RenderHelp::DrawSquareColorA(16*x,16*y,16,16,0,0,0, ShadeMap[y][x] );
        }
}
