#include "title.hpp"
#include "../camera.hpp"
#include <omp.h>

Title::Title(){
    Camera::SetHW(640,480);
    Camera::Follow(NULL);
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    requestQuit = requestDelete = false;
    introStage = 1;
    bg = new Sprite("img/grass.jpg");
    int sz = 16;
    lightSystem = new Shader(640,480,sz);
    /*
    for (int i=0;i<10;i++){
        int x = rand()%(640/sz  -2);
        int y = rand()%(480/sz  -2);
        lightSystem->AddBlock(x,y,255);
        lightSystem->AddBlock(x+1,y,255);
        lightSystem->AddBlock(x,y+1,255);
        lightSystem->AddBlock(x+1,y+1,255);
    }*/


    blockSize_t = new Text("font1.otf",12,TEXT_SOLID,"32x32",{0,0,255});
    TtoRender_t = new Text("font1.otf",12,TEXT_SOLID,"Time to render",{0,0,255});
    time_tt = new Text("font1.otf",12,TEXT_SOLID,"0",{0,0,255});


}



Title::~Title(){
    delete bg;
    delete blockSize_t;
    delete time_tt;
    delete TtoRender_t;

    std::cout << "Closed title\n";
}


void Title::Update(float dt){
    //lightSystem->ClearLights();

    Input();



    double bgn = omp_get_wtime();

    lightSystem->Update(dt);
    double end = omp_get_wtime();
    char str[100];
    sprintf(str,"%.5lf",end-bgn);
    time_tt->SetText(str);

}


void Title::Render(){

    static int cycle = 0;
    cycle++;
    SDL_SetRenderDrawColor(Game::instance->GetRenderer(), 0, 0,0, 0);
    SDL_RenderClear( Game::instance->GetRenderer() );
    bg->Render(0,0);
    lightSystem->Render();

    RenderHelp::DrawSquareColorA(0,480,640,80,255,255,255,255);

    blockSize_t->Render(10,490,255);
    TtoRender_t->Render(70,490,255);
    time_tt->Render(200,490,255);


}
void Title::Input(){
    KeyBind *bind = InputManager::GetInstance().GetKeyBinds();
    if (InputManager::GetInstance().ShouldQuit()){
        requestQuit = true;
    }
    if (InputManager::GetInstance().KeyPress(bind->K_UP)){
        lightSystem->SetMaxCycles(10);
    }
    if (InputManager::GetInstance().KeyPress(bind->K_DOWN)){
        lightSystem->SetMaxCycles(-10);
    }
    if (InputManager::GetInstance().MousePress(1)){
        lightSystem->AddLight(InputManager::GetInstance().GetMouseX()/16,InputManager::GetInstance().GetMouseY()/16,rand()%255);
    }
    if (InputManager::GetInstance().MousePress(3)){
        lightSystem->AddBlock(InputManager::GetInstance().GetMouseX()/16,InputManager::GetInstance().GetMouseY()/16,255);
    }
    if (InputManager::GetInstance().KeyPress(SDLK_l)){
        lightSystem->ClearLights();
    }


}
