
#ifndef CONFIGH
#define CONFIGH
#include "SDL2/SDL.h"



class ConfigManager{
    public:

        double ScaleRatioH(){return scaleRatioH;};
        double ScaleRatioHTrue(){return scaleRatioHT;};
        double ScaleRatioW(){return scaleRatioW;};
        double ScaleRatioWTrue(){return scaleRatioWT;};
        double OffsetW(){return OffW;};
        int GetScreenH(){return ScreenH;};
        int GetScreenW(){return ScreenW;};
        double GetUIscale(){return UIscale;};
        double GetGlobalScale(){return SprScale;};
        void Resize(double w,double h);
        void SetEnableResize(bool r);
        void SetWindowHW(int w,int h);
        void Resize();
        bool IsResized(){ if (resized){ resized = false; return true;}else return false; };
        static ConfigManager& GetInstance();
        ConfigManager();
        ~ConfigManager();
        bool pause,UseLight;
    private:
        int ScreenH,ScreenW;
        int ScreenHT,ScreenWT;
        bool resized;
        double OffW,scaleRatioWT,scaleRatioHT;
        double UIscale,SprScale,ResizedW,ResizedH,scaleRatioW,scaleRatioH;


};
#endif

