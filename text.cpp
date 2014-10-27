#include "text.hpp"
std::unordered_map<std::string, TTF_Font*> Text::assetTable;
std::unordered_map<std::string, CustomFont*> Text::customTable;

CustomFont::CustomFont(std::string pngfile,std::string letterpositions){
    sp = new Sprite(pngfile.c_str());
    Letters[(unsigned char)'a'] = std::unique_ptr<Letter>(new Letter(1,0,17,7,0,0));
    Letters[(unsigned char)'c'] = std::unique_ptr<Letter>(new Letter(16,0,17,7,0,0));
    Letters[(unsigned char)'b'] = std::unique_ptr<Letter>(new Letter(9,0,17,7,0,0));
    Letters[(unsigned char)'d'] = std::unique_ptr<Letter>(new Letter(24,0,17,6,0,0));
    Letters[(unsigned char)'e'] = std::unique_ptr<Letter>(new Letter(31,0,17,7,0,0));
    Letters[(unsigned char)'f'] = std::unique_ptr<Letter>(new Letter(38,0,17,6,0,0));
    Letters[(unsigned char)'g'] = std::unique_ptr<Letter>(new Letter(44,0,17,8,0,0));
    Letters[(unsigned char)'h'] = std::unique_ptr<Letter>(new Letter(53,0,17,7,0,0));
    Letters[(unsigned char)'i'] = std::unique_ptr<Letter>(new Letter(59,0,17,4,0,0));
    Letters[(unsigned char)'j'] = std::unique_ptr<Letter>(new Letter(63,0,17,5,0,0));
    Letters[(unsigned char)'k'] = std::unique_ptr<Letter>(new Letter(69,0,17,6,0,0));
    Letters[(unsigned char)'l'] = std::unique_ptr<Letter>(new Letter(76,0,17,2,0,0));
    Letters[(unsigned char)'m'] = std::unique_ptr<Letter>(new Letter(78,0,17,12,0,0));
    Letters[(unsigned char)'n'] = std::unique_ptr<Letter>(new Letter(90,0,17,6,0,0));
    Letters[(unsigned char)'o'] = std::unique_ptr<Letter>(new Letter(98,0,17,5,0,0));
    Letters[(unsigned char)'p'] = std::unique_ptr<Letter>(new Letter(104,0,17,7,0,0));
    Letters[(unsigned char)'q'] = std::unique_ptr<Letter>(new Letter(111,0,17,6,0,0));
    Letters[(unsigned char)'r'] = std::unique_ptr<Letter>(new Letter(119,0,17,5,0,0));
    Letters[(unsigned char)'s'] = std::unique_ptr<Letter>(new Letter(126,0,17,5,0,0));
    Letters[(unsigned char)'t'] = std::unique_ptr<Letter>(new Letter(131,0,17,6,0,0));
    Letters[(unsigned char)'u'] = std::unique_ptr<Letter>(new Letter(139,0,17,6,0,0));
    Letters[(unsigned char)'v'] = std::unique_ptr<Letter>(new Letter(147,0,17,7,0,0));
    Letters[(unsigned char)'w'] = std::unique_ptr<Letter>(new Letter(155,0,17,10,0,0));
    Letters[(unsigned char)'x'] = std::unique_ptr<Letter>(new Letter(166,0,17,6,0,0));
    Letters[(unsigned char)'y'] = std::unique_ptr<Letter>(new Letter(173,0,17,7,0,0));
    Letters[(unsigned char)'z'] = std::unique_ptr<Letter>(new Letter(183,0,17,5,0,0));


    Letters[(unsigned char)'A'] = std::unique_ptr<Letter>(new Letter(0,18,17,8,0,0));
    Letters[(unsigned char)'B'] = std::unique_ptr<Letter>(new Letter(11,18,17,8,0,0));
    Letters[(unsigned char)'C'] = std::unique_ptr<Letter>(new Letter(22,18,17,8,0,0));
    Letters[(unsigned char)'D'] = std::unique_ptr<Letter>(new Letter(34,18,17,8,0,0));
    Letters[(unsigned char)'E'] = std::unique_ptr<Letter>(new Letter(44,18,17,8,0,0));
    Letters[(unsigned char)'F'] = std::unique_ptr<Letter>(new Letter(53,18,17,6,0,0));
    Letters[(unsigned char)'G'] = std::unique_ptr<Letter>(new Letter(61,18,17,9,0,0));
    Letters[(unsigned char)'H'] = std::unique_ptr<Letter>(new Letter(72,18,17,8,0,0));
    Letters[(unsigned char)'I'] = std::unique_ptr<Letter>(new Letter(83,18,17,7,0,0));
    Letters[(unsigned char)'J'] = std::unique_ptr<Letter>(new Letter(91,18,17,8,0,0));
    //j
    //k
    Letters[(unsigned char)'L'] = std::unique_ptr<Letter>(new Letter(101,18,17,8,0,0));
    //m
    Letters[(unsigned char)'N'] = std::unique_ptr<Letter>(new Letter(122,18,17,10,0,0));
    Letters[(unsigned char)'O'] = std::unique_ptr<Letter>(new Letter(134,18,17,9,0,0));
    //p
    //q
    //r
    //s
    Letters[(unsigned char)'S'] = std::unique_ptr<Letter>(new Letter(178,18,17,8,0,0));
    Letters[(unsigned char)'T'] = std::unique_ptr<Letter>(new Letter(189,18,17,8,0,0));
    //u
    //v
    //w
    //x
    //y
    //z
    Letters[(unsigned char)'\n'] = std::unique_ptr<Letter>(new Letter(0,0,17,0,0,0));
}
CustomFont::~CustomFont(){
    delete sp;
    Letters.clear();
}

Point CustomFont::Render(std::string str_,int x,int y){
    Point p;
    p.x = 0;
    p.y = 0;
    unsigned char *str = (unsigned char *)str_.c_str();
    int beginx = x;
    int beginy = y;
    for (int i=0;i<str_.size();i++){
        if (str[i] == 13)
            continue;
        if (!Letters[str[i]]){
            sp->SetClip(192,0,17,6);
            sp->Render(x,y);
            x += 6 ;
        }else{
            Letter l = *Letters[str[i]].get();
            if (l.x == 0){
                x = beginx;
                y += l.h;
            }else{
                sp->SetClip(l.x,l.y,l.h,l.w);
                sp->Render(x+l.padin,y);
                x+= l.w + l.pad;
            }
        }
    }
    p.x = x-beginx;
    p.y = y-beginy+17;
    return p;
}
Text::Text(std::string fontfilep, int fontsize,TextStyle stylep, std::string textp, SDL_Color colot,int x,int y){
    angle = 0;
    SDLFONT = true;
    box.x = x;
    box.y = y;
    text = textp;
    bg = {0,0,0,0};
    size = fontsize;
    style = stylep;
    color = colot;
    texture = NULL;
    std::string ftnm = fontfilep;
    char buff[10];
    sprintf(buff,"%d",fontsize);
    ftnm = ftnm+buff;
    fontfile = fontfilep;
    if (assetTable[ftnm]){
        font =assetTable[ftnm];
    }else{
        printf("Loading font %s\n",fontfilep.c_str());
        font = TTF_OpenFont(fontfilep.c_str(), fontsize);
        if (font != NULL){
            assetTable[ftnm] = font;
        }
    }
    if (font){
        RemakeTexture();
    }
    texturespr = NULL;
    scaleY=scaleX=1;


}

Text::Text(std::string fontfilep, std::string textp,int x,int y){
    angle = 0;
    SDLFONT = false;
    box.x = x;
    box.y = y;
    text = textp;
    bg = {0,0,0,0};
    texture = NULL;
    std::string ftnm = fontfilep;
    if (customTable[fontfilep]){
        texturespr = customTable[fontfilep];
    }else{
        texturespr = customTable[fontfilep] = new CustomFont(fontfilep,fontfilep);
    }

    scaleY=scaleX=1;



}
Text::~Text(){
    if (texture){
        SDL_DestroyTexture( texture );
    }
}
void Text::Render(int cameraX,int cameraY,int alpha){
    if (SDLFONT){
        SDL_Rect dimensions2;
        double scaleRatioW = ConfigManager::GetInstance().ScaleRatioW();
        double scaleRatioH = ConfigManager::GetInstance().ScaleRatioH();
        dimensions2.x = box.x*scaleRatioW+cameraX*scaleRatioW+ ConfigManager::GetInstance().OffsetW();
        dimensions2.y = box.y*scaleRatioH+cameraY*scaleRatioH;
        dimensions2.h = box.h*scaleRatioH*scaleY;
        dimensions2.w = box.w*scaleRatioW*scaleY;
        alpha = alpha < 0 ? 0 : alpha;
        alpha = alpha > 255 ? 255 : alpha;

        SDL_SetTextureAlphaMod(texture,alpha);
        //SDL_RenderCopy(Game::instance->GetRenderer(),texture,NULL,&dimensions2);
        SDL_RenderCopyEx(Game::instance->GetRenderer(),texture,NULL,&dimensions2,static_cast<double>(angle),nullptr,SDL_FLIP_NONE); //wat
    }else{
        Point p = texturespr->Render(text,box.x+cameraX,box.y+cameraY);
        box.w = p.x;
        box.h = p.y;
    }
}

void Text::SetPos(int x,int y,bool cx=false,bool cy=false){
    box.x = x;
    box.y = y;
}

void Text::SetText(std::string str){
    if (!SDLFONT)
        return;
    text = str;
    RemakeTexture();
}
void Text::SetColor(SDL_Color col ){
    if (!SDLFONT)
        return;
    color = col;
    RemakeTexture();
}
void Text::SetStyle(TextStyle syle){
    if (!SDLFONT)
        return;
    style = syle;

}
void Text::SetFontSize(int ftsz){
    if (!SDLFONT)
        return;
    std::string ftnm = fontfile;
    char buff[10];
    sprintf(buff,"%d",ftsz);
    ftnm = ftnm+buff;

    if (assetTable[ftnm]){
        font =assetTable[ftnm];
    }else{
        fontfile = ftnm;
        font = TTF_OpenFont(fontfile.c_str(), ftsz);
        if (font != NULL){
            assetTable[ftnm] = font;
        }
    }
    if (font){
        RemakeTexture();
    }
}
void Text::Clear(){
    assetTable.clear();
    //Fix
    //TTF_CloseFont(TTF_Font* font)

}
//private
void Text::RemakeTexture(){
    if (!SDLFONT)
        return;
    if (texture){
        SDL_DestroyTexture( texture );
    }
    texture = NULL;
    SDL_Surface *surf=NULL;
    if (style == TEXT_SOLID){
        surf = TTF_RenderText_Solid(font,text.c_str(),color);
    }else if(style == TEXT_SHADED){
        surf = TTF_RenderText_Shaded(font, text.c_str(),color, bg);
    }else if(style == TEXT_BLENDED){
        surf = TTF_RenderText_Blended(font,text.c_str(),color);
    }
    if (surf){
        texture = SDL_CreateTextureFromSurface(Game::instance->GetRenderer(),surf);
        Uint32 format;
        int acess;
        SDL_QueryTexture(texture, &format,&acess,&w,&h);
        box.h=h;
        box.w=w;
        SDL_FreeSurface(surf);
    }
}
