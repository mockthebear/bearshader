
#ifndef GAMEBASEH
#define GAMEBASEH


#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <string.h>

#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "state.hpp"
#include "inputmanager.hpp"
#include "configmanager.hpp"



class Game{

    public:
        void Run();
        SDL_Renderer* GetRenderer() {return renderer;};
        SDL_Texture * GeBackBuffer() {return backBuffer;};
        SDL_Texture * backBuffer;
        SDL_Window* GetWindow() {return window;};
        State &GetCurrentState();
        static Game* GetInstance ();
        Game(char *title,int h,int w);
        virtual ~Game();
        void Update();
        void Render();
        static Game* instance;
        float GetDeltaTime(){return (dt-frameStart)/100.0;};
        void CalculateDeltaTime(){dt = SDL_GetTicks();};
         void AddState(State *s){storedState = s;};
         std::stack<std::unique_ptr<State>> stateStack;
         bool canDelete,canDebug;
         bool isClosing;
    private:

        State *storedState;
        void UpdateTitleAsFps(float);
        SDL_Renderer* renderer;
        unsigned int nextUpdate;
        char title[500];
        int frameStart,frames,olt;
        float dt;

        SDL_Window* window;

};
#endif
