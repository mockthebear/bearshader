#ifndef SHADER_
#define SHADER_


class Shader{
    public:
        Shader(int sx,int sy,int blockhw);
        ~Shader();



        void AddLight(int,int,unsigned char);

        void Render();
        void Update(float dt);
        //Config
        void SetMaxCycles(int n);
    private:
        //Envoriment
        int GetAround(unsigned char**,int x,int y);
        unsigned char ** ShootLightRay(int,int,unsigned char, unsigned char **, unsigned char **);

        bool IsInLimits(int,int);
        unsigned char **ShadeMap,**DataMap;
        unsigned char*** Maps,***Mapsaux;
        int sizeX,sizeY,blockSize;
        int MaxCycles,UseThreads;
        //Ambient
        float PermissiveAmbient;
};
#endif // SHADER_
