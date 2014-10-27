#include "smarttexture.hpp"
#include "gamebase.hpp"
SmartTexture::SmartTexture(int xx,int yy,int ww,int hh){
   t = SDL_CreateTexture( Game::instance->GetRenderer(),SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, ww, hh);
   pixels = new Uint32[w * h];
   SDL_SetTextureBlendMode( t, SDL_BLENDMODE_BLEND );
   x = xx;
   y = yy;
}


void SmartTexture::UpdateTexture(){
    SDL_UpdateTexture(t, NULL, pixels, w * sizeof(Uint32));
}
SmartTexture::~SmartTexture(){

    delete []pixels;
}
void SmartTexture::Render(int xx,int yy){
    double scaleRatioW = floor(ConfigManager::GetInstance().ScaleRatioW()*(w+0.0))/(w+0.0); //floor(ConfigManager::GetInstance().ScaleRatioW()*32.1)/32.1
    double scaleRatioH = floor(ConfigManager::GetInstance().ScaleRatioH()*(h+0.0))/(h+0.0); //floor(ConfigManager::GetInstance().ScaleRatioW()*32.1)/32.1
    SDL_Rect rr;
    rr.x = round((double)(x+xx)*scaleRatioW);
    rr.y = round((double)(y+yy)*scaleRatioH);
    rr.h = round((double)(h)*scaleRatioH);
    rr.w = round((double)(w)*scaleRatioW);
    SDL_RenderCopyEx(Game::instance->GetRenderer(),t,NULL,&rr,0,nullptr,SDL_FLIP_NONE); //wat
}

