#include "configmanager.hpp"
#include "gamebase.hpp"

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"


ConfigManager::ConfigManager(){
    ScreenHT = ScreenWT = 0;
    scaleRatioHT = scaleRatioWT = 1.0f;
    ScreenW=640;
    ScreenH=520;
    UIscale=1;
    SprScale=1;
    ResizedW=ScreenW;
    ResizedH=ScreenH;
    scaleRatioW = 1.0;
    scaleRatioH = 1.0;
    pause = false;
    UseLight=true;
    OffW = 0;
    resized = false;


}


ConfigManager::~ConfigManager(){


}
void ConfigManager::SetEnableResize(bool r){

}
void ConfigManager::SetWindowHW(int w,int h){
    ScreenW=w;
    ScreenH=h;
    Resize(w,h);
}
void ConfigManager::Resize(double w,double h){
    SDL_SetWindowSize(Game::GetInstance()->GetWindow(),w,h);
}

void ConfigManager::Resize(){
    int w,h;
    static int counter = 0;
    resized = true;
    SDL_GetWindowSize(Game::GetInstance()->GetWindow(), &w, &h);
    scaleRatioW =  ( (double)w / ScreenW);
    scaleRatioH =  ( (double)h / ScreenH);
    //std::cout << "Scale: " << scaleRatioH << " to ";
    scaleRatioWT = scaleRatioW = round(scaleRatioW*2.0)/2.0;
    scaleRatioHT = scaleRatioH = round(scaleRatioH*2.0)/2.0;
    //std::cout << scaleRatioH << " > " << ScreenH << " > " << h <<" \n" ;

    scaleRatioW = scaleRatioH;
    if ( scaleRatioH*ScreenH > h ){
        std::cout << "Fail " << scaleRatioH*ScreenH - h << " - " << counter <<std::endl;
        counter++;
        h -= (scaleRatioH*ScreenH - h);
        if (counter > 10){
            counter = 0;
            Resize(640,480);
        }
    }else{
        counter = 0;
    }


    ResizedW=w;
    ResizedH=h;
    OffW = ScreenW == w ? 0 : w/2 - (ScreenW/2)*scaleRatioW;



}
ConfigManager& ConfigManager::GetInstance(){
    static ConfigManager teste;
    return teste;
}

