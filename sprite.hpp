#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


#ifndef SPRITEHA
#define SPRITEHA


#include <unordered_map>
#include <string>
class Sprite{
    public:
        Sprite();
        Sprite(char *file,int fcount=1,float ftime = 1);
        Sprite(const char *file,int fcount=1,float ftime = 1);
        ~Sprite();
        void Open (char *file);
        void SetClip (int x,int y,int w,int h);
        void Render (int x,int y,double angle=0);
        SDL_Texture* GetTexture(){return texture;};
        void Update(float dt);
        void SetFrame(int f);
        void SetFrameCount(int fc){frameCount=fc;};
        void SetFrameTime(float ft){frameTime=ft;};
        int GetWidth();
        int GetHeight();
        bool IsOpen(){return texture != NULL;};
        static std::unordered_map<std::string, SDL_Texture*> assetTable;
        static void Clear();
        bool IsAnimationOver(){return over;};
        void SetScaleX(float scale){scaleX=scale;};
        void SetScaleY(float scale){scaleY=scale;};
        uint8_t OUTR,OUTB,OUTG;
        void ReBlend(){SDL_SetTextureColorMod(texture,OUTR,OUTB,OUTG);};
        void SetAlpha(int a){ SDL_SetTextureAlphaMod(texture,a);};
    private:
        float scaleX,scaleY,timeElapsed,frameTime;
        bool over;
        int frameCount,currentFrame;
        SDL_Texture* texture;
        SDL_Rect dimensions;
        SDL_Rect clipRect;
};

#endif
