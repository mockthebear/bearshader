#ifndef SHADER_
#define SHADER_
#include "../sprite.hpp"

class Shader{
    public:
        Shader(int sx,int sy,int blockhw);
        ~Shader();

        static Shader& GetInstance(int sx = 640,int sy = 480,int sz = 16);

        bool AddLight(int,int,unsigned char);
        void AddBlock(int,int,unsigned char);

        void ClearLights();

        void Render();
        void Update(float dt);
        //Config
        void SetMaxCycles(int n);
        int GetPthreads(){return UsePThreads;};
        int GetOpenmp(){return UseThreads;};

        int SetOpenmp(int n){UseThreads = std::min(16,std::max(1,n));};
        int SetPthreads(int n){UsePThreads = std::min(16,std::max(1,n));};

        bool IsInLimits(int,int);
        unsigned char **ShadeMap,**DataMap;
        float PermissiveAmbient;
    private:
        //Envoriment
        //static void parallellight__(void*);
        int GetAround(unsigned char**,int x,int y);
        unsigned char ** ShootLightRay(int,int,unsigned char, unsigned char **);



        unsigned char*** Maps,***Mapsaux;
        int sizeX,sizeY,blockSize;
        int MaxCycles,UseThreads,UsePThreads;
        //Ambient

        Sprite *light,*block;
};

typedef struct{
    int dis,Threads,x,y,MaxCycles;
    unsigned char strenght;
    Shader *MINE;
    unsigned char ** ShadeMapAux;
} parameters;


#endif // SHADER_
