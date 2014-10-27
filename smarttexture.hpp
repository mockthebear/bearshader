#ifndef SMTXH
#define SMTXH
#include <SDL2/SDL.h>
#include <stdint.h>
#include <functional>
class SmartTexture{
    public:
        SmartTexture(int x,int y,int h,int w);
        SmartTexture(SDL_Texture *tex,Uint32 *p,int xx,int yy,int hh,int ww):t(tex),pixels(p),h(hh),w(ww),x(xx),y(yy){};
        void CallLambda(std::function<void (Uint32 *, int, int)> F){ F(pixels,h,w);};
        ~SmartTexture();
        void Render(int x,int y);
        void UpdateTexture();
        Uint32 *GetPixels(){return pixels;};
        SDL_Texture * GetTexture(){return t;};
    private:
        SDL_Texture *t;
        Uint32 * pixels;
        int h,w;
        int x,y;

};


#endif //
