#include "renderhelp.hpp"
#include <stdio.h>


void RenderHelp::DrawSquareColorA(int x,int y,int h,int w,int r,int g,int b,int a){

    SDL_SetRenderDrawColor(Game::instance->GetRenderer(), r, g,b, a);
    SDL_Rect rectangle;
    double scaleRatioW = (ConfigManager::GetInstance().ScaleRatioW());
    double scaleRatioH = (ConfigManager::GetInstance().ScaleRatioH());
    rectangle.x = ( x*scaleRatioW  )+ ConfigManager::GetInstance().OffsetW();
    rectangle.y = ( y*scaleRatioH  );
    rectangle.w = ( h*scaleRatioW  );
    rectangle.h = ( w*scaleRatioH  );
    SDL_RenderFillRect(Game::instance->GetRenderer(), &rectangle);
}

SmartTexture *RenderHelp::GeneratePatternTexture(int x,int y,int w,int h){
    SDL_Texture *t = SDL_CreateTexture( Game::instance->GetRenderer(),SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, w, h);
    Uint32 * pixels = new Uint32[w * h];

    SDL_SetTextureBlendMode( t, SDL_BLENDMODE_BLEND );

    for (int y = 0;y < h;y++){
        for (int x=0;x<w;x++){
             pixels[y * h + x] = RenderHelp::FormatRGBA(rand()%255,rand()%255,rand()%255, rand()%255);
        }
    }
    SDL_UpdateTexture(t, NULL, pixels, w * sizeof(Uint32));
	return new SmartTexture(t,pixels,x,y,h,w);

}

SmartTexture *RenderHelp::GeneratePatternTexture(int x,int y,int w,int h,std::function<Uint32 (Uint32 , int, int)> F){
    SDL_Texture *t = SDL_CreateTexture( Game::instance->GetRenderer(),SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, w, h);
    Uint32 * pixels = new Uint32[w * h];

    SDL_SetTextureBlendMode( t, SDL_BLENDMODE_BLEND );
    for (int y = 0;y < h;y++){
        for (int x=0;x<w;x++){
             pixels[y * h + x] = F(pixels[y * h + x],x,y);
        }
    }
    SDL_UpdateTexture(t, NULL, pixels, w * sizeof(Uint32));
	return new SmartTexture(t,pixels,x,y,h,w);
}
Uint32 RenderHelp::FormatRGBA(int r,int b,int g,int a){

    Uint32 R,G,B;
    R = r << (24);
    G = g << 16;
    B = b << 8;
    return R+G+B+a;
}
