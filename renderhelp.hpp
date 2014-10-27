#ifndef RENDERH
#define RENDERH
#include "gamebase.hpp"
#include "smarttexture.hpp"

#include <functional>



class RenderHelp{
    public:
        static void DrawSquareColorA(int x,int y,int h,int w,int r,int g,int b,int a=255);
        static SmartTexture *GeneratePatternTexture(int x,int y,int h,int w,std::function<Uint32 (Uint32 , int, int)> F);
        static SmartTexture *GeneratePatternTexture(int x,int y,int h,int w);

        static Uint32 FormatRGBA(int r,int b,int g,int a);
};


#endif
