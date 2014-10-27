#include "geometry.hpp"
#include "gamebase.hpp"
#include "sprite.hpp"
#include "SDL2/SDL_ttf.h"
#include <unordered_map>
#include <string>

#ifndef TEXTH
#define TEXTH

enum TextStyle{
    TEXT_SOLID,
    TEXT_SHADED,
    TEXT_BLENDED
};


class Letter{
    public:
        Letter(int xx,int yy,int hh, int ww, int ppad,int ppadin){
            x = xx;
            y = yy;
            h = hh;
            w = ww;
            pad = ppad;
            padin = ppadin;
        }
        int x,y,h,w,pad,padin;
};

class CustomFont{
    public:
        CustomFont(std::string pngfile,std::string letterpositions);
        ~CustomFont();
        Point Render(std::string str,int x,int y);
    private:
        Sprite *sp;
        std::unordered_map<unsigned char, std::unique_ptr<Letter>> Letters;
};

class Text{
    public:
        Text(std::string fontfile, int fontsize,TextStyle style, std::string text, SDL_Color colot,int x=0,int y=0);
        Text(std::string fontfile, std::string text,int x=0,int y=0);
        ~Text();
        void Render(int cameraX = 0, int cameraY = 0,int alpha = 255);
        void SetPos(int x,int y,bool centerX,bool centerY);
        void SetText(std::string str);
        void SetColor(SDL_Color colot);
        void SetStyle(TextStyle style);
        std::string GetText(){return text;};
        float GetH(){return box.h*scaleY;};
        float GetW(){return box.w*scaleX;};
        void SetFontSize(int size);
        static void Clear();
        void SetScaleX(float scale){scaleX=scale;};
        void SetScaleY(float scale){scaleY=scale;};
        void RemakeTexture();
        SDL_Color bg;
        float angle;
    private:
        int h,w;
        bool SDLFONT;
        TTF_Font* font;
        SDL_Texture* texture;
        CustomFont *texturespr;
        std::string fontfile,text;
        TextStyle style;
        int size;
        float scaleY,scaleX;
        SDL_Color color;
        Rect box;
        static std::unordered_map<std::string, TTF_Font*> assetTable;
        static std::unordered_map<std::string, CustomFont*> customTable;


};

#endif
