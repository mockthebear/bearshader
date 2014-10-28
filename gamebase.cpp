#include "gamebase.hpp"
#include <time.h>
#define MAXFPS 40
#include "shader/title.hpp"
Game* Game::instance = NULL;

Game::Game(char *title_,int w,int h){
    if (instance == NULL){
        isClosing = false;
        instance = this;
        canDebug = false;
        backBuffer = NULL;
        canDelete = false;
        if (not SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK)){
            std::cout <<"Sdl started.";
        }
        if (not IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)){
            printf("IMG FAIL");
        }
        if (TTF_Init()  == -1 ){
            printf("TTF FAIL");
        }

        window = SDL_CreateWindow( title_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE ); //SDL_WINDOW_RESIZABLE
        strcpy(title,title_);
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer){
            printf("Fail render!");
        }

        SDL_SetRenderDrawBlendMode(GetRenderer(),SDL_BLENDMODE_BLEND);

        dt = frameStart = frames = 0;
        nextUpdate =  1000;
        CalculateDeltaTime();
        srand(time(NULL));

        storedState  =new Title();
        olt = SDL_GetTicks();
        InputManager::GetInstance().InitJoySticks();


    }

}


Game::~Game(){
    stateStack.pop();
    //delete title;
    isClosing = true;
    printf("Closing!\n");
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );

    printf("Closing text\n");
    TTF_Quit();

    printf("Closing img\n");
    IMG_Quit();
    printf("Closing sdl\n");
    SDL_Quit();
    std::cout << "Quit game.\n";

}

Game *Game::GetInstance(){
    return instance;
}
void Game::Update(){
    float dt = std::min(GetDeltaTime(),1.2f );
    stateStack.top()->Update(dt);
}
void Game::Render(){
    stateStack.top()->Render();
}

void Game::UpdateTitleAsFps(float w8){

    if (nextUpdate <= SDL_GetTicks()){
        char Buff[100];
        sprintf(Buff,"%s (FPS: %f) = %f  = %f",title,frames*1000.0/(1000.0-(SDL_GetTicks()-olt)),GetDeltaTime(),w8);
        SDL_SetWindowTitle(window, Buff);
        olt = SDL_GetTicks()+1000;
        nextUpdate = olt;
        frames = 0;
    }
}
void Game::Run(){
    if (storedState != NULL){
        stateStack.emplace(storedState);
        storedState =NULL;
    }

    while (!SDL_QuitRequested() and not stateStack.top()->RequestedQuit()){
        restart_cycle:
        frameStart = dt;
        CalculateDeltaTime();

        InputManager::GetInstance().Update();
        if (ConfigManager::GetInstance().IsResized())
            goto restart_cycle;
        Update();
        if (InputManager::GetInstance().KeyPress(SDLK_F11)){
            static bool full = false;
            if (!full)
                SDL_SetWindowFullscreen(window, SDL_TRUE);
            else
                SDL_SetWindowFullscreen(window, SDL_FALSE);
            full = !full;
        }

        Render();
        SDL_RenderPresent(GetRenderer() );

        //Limitar dinamicamente o tempo de cada frame para atingir sempre que possivel 30 fps
        float n = GetDeltaTime()*100.0;

        if (stateStack.top()->RequestedDeleted()){
            if (stateStack.empty() && storedState == NULL){
                break;
            }else{
                stateStack.pop();
            }
        }

        if (storedState != NULL){
            stateStack.emplace(storedState);
            stateStack.top()->Begin();
            storedState =NULL;
        }


        n = n-(1000.0/MAXFPS);
        n  = n < 0 ? 0 : n;
        n  = (1000.0/MAXFPS)-n < 0 ? 0 : n;


        SDL_Delay( std::max( (1000.0/MAXFPS)-n - 5, 0.0) );

        frames++;
        UpdateTitleAsFps((1000.0/MAXFPS)-n  );

    }
    isClosing = true;


};
State &Game::GetCurrentState(){
    return *stateStack.top();
}
