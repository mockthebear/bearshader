#include "sprite.hpp"
#include "gamebase.hpp"
#include <math.h>

std::unordered_map<std::string, SDL_Texture*> Sprite::assetTable;
Sprite::Sprite(){
    scaleX = scaleY = 1;
    texture = NULL;
    OUTR = OUTB = OUTG = 255;
}

Sprite::Sprite(char *file,int fcount,float ftime){
    frameCount = fcount;
    currentFrame = 0;
    timeElapsed = 0;
    frameTime = ftime;
    texture = NULL;
    Open(file);
    SetFrame(0);
    over = false;
    OUTR = OUTB = OUTG = 255;
}

Sprite::Sprite(const char *file,int fcount,float ftime){
    frameCount = fcount;
    currentFrame = 0;
    timeElapsed = 0;
    frameTime = ftime;
    texture = NULL;

    Open((char *)file);
    SetFrame(0);
    OUTR = OUTB = OUTG = 255;
}

void Sprite::Update(float dt){
    timeElapsed = timeElapsed+dt*100;
    if (timeElapsed >= frameTime){
        timeElapsed = 0;
        currentFrame++;
        if (currentFrame >= frameCount){
            currentFrame = 0;
            over = true;
        }
        SetFrame(currentFrame);
    }
}
void Sprite::SetFrame(int dt){
    currentFrame = dt;
    if (currentFrame >= frameCount){
        currentFrame = 0;
    }
    SetClip(currentFrame*(GetWidth()/frameCount), 0,GetHeight(),GetWidth()/frameCount);
}

Sprite::~Sprite(){}

void Sprite::Clear(){
    printf("Clearing sprites\n");

    //Fix
    assetTable.clear();
}
void Sprite::Open(char *file){
    scaleX = scaleY = 1;
    std::string stdnamee(file);
    if (assetTable.find(stdnamee) == assetTable.end()){

        texture = IMG_LoadTexture(Game::instance->GetRenderer(),file);
        if (texture != NULL){
            Uint32 format;
            int acess;
            SDL_QueryTexture(texture, &format,&acess,&dimensions.w,&dimensions.h);
            SetClip(0,0,dimensions.h,dimensions.w);
            assetTable[stdnamee] = texture;
            printf("Loaded %s\n",file);
        }else{
           printf("Cannot load [%s] sprite\n",file);
        }
    }else{
        std::unordered_map<std::string, SDL_Texture*>::iterator it = assetTable.find(stdnamee);
        texture = (*it).second;
        if (texture){
            Uint32 format;
            int acess;
            SDL_QueryTexture(texture, &format,&acess,&dimensions.w,&dimensions.h);
            SetClip(0,0,dimensions.h,dimensions.w);
        }
    }


}

void Sprite::SetClip(int x, int y,int h,int w){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.h = h;
    clipRect.w = w;

}
void Sprite::Render(int x, int y,double angle){
    SDL_Rect dimensions2;

    double scaleRatioW = ConfigManager::GetInstance().ScaleRatioW(); //floor(ConfigManager::GetInstance().ScaleRatioW()*32.1)/32.1
    double scaleRatioH = ConfigManager::GetInstance().ScaleRatioH(); //floor(ConfigManager::GetInstance().ScaleRatioW()*32.1)/32.1
    dimensions2.x = x*scaleRatioW + ConfigManager::GetInstance().OffsetW();
    dimensions2.y = y*scaleRatioH;
    dimensions2.h = clipRect.h*scaleRatioH*scaleY;
    dimensions2.w = clipRect.w*scaleRatioW*scaleX;
    SDL_RenderCopyEx(Game::instance->GetRenderer(),texture,&clipRect,&dimensions2,static_cast<double>(angle),nullptr,SDL_FLIP_NONE); //wat
}

int Sprite::GetWidth(){
    return dimensions.w*scaleX;
}

int Sprite::GetHeight(){
    return dimensions.h*scaleY;
}
