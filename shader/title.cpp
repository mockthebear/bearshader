#include "title.hpp"
#include "../camera.hpp"
#include <omp.h>
#include <sys/time.h>

Title::Title(){
    Camera::SetHW(640,480);
    Camera::Follow(NULL);
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    requestQuit = requestDelete = false;
    introStage = 1;
    bg = new Sprite("img/grass.jpg");
    int sz = 16;
    Shader::GetInstance(640,480,sz);
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
    struct timeval bgn, end;


    //double bgn = omp_get_wtime();
    gettimeofday(&bgn, NULL);
    Shader::GetInstance().Update(dt);
    gettimeofday(&end, NULL);
    //double end = omp_get_wtime();
    double dur = (  (end.tv_usec - bgn.tv_usec) /100000.0);
    char str[100];
    //leTime = (end.tv_usec - bgn.tv_usec) /1555.0;
    sprintf(str,"%.5lf",dur);
    time_tt->SetText(str);

}


void Title::Render(){

    static int cycle = 0;

    //SDL_SetRenderDrawColor(Game::instance->GetRenderer(), 0, 0,0, 0);
    //SDL_RenderClear( Game::instance->GetRenderer() );
    bg->Render(0,0);
    Shader::GetInstance().Render();

    //RenderHelp::DrawSquareColorA(0,480,1,80,255,255,255,255);
    RenderHelp::DrawSquareColorA(0,480,290,80,255,255,255,255);

    blockSize_t->Render(10,490,255);
    TtoRender_t->Render(70,490,255);

    time_tt->Render(200,490,255);
    if (Game::GetInstance()->updateFPS){
        lfps=Game::GetInstance()->FPS;
        RenderHelp::DrawSquareColorA(300+cycle,520 - lfps,1,1,255,255,255,255);
        RenderHelp::DrawSquareColorA(300+cycle,520 - leTime,1,1,255,0,0,255);
        cycle++;
    }


}
void Title::Input(){
    KeyBind *bind = InputManager::GetInstance().GetKeyBinds();
    if (InputManager::GetInstance().ShouldQuit()){
        requestQuit = true;
    }
    if (InputManager::GetInstance().KeyPress(bind->K_UP)){
        Shader::GetInstance().SetMaxCycles(10);
    }
    if (InputManager::GetInstance().KeyPress(bind->K_DOWN)){
        Shader::GetInstance().SetMaxCycles(-10);
    }
    if (InputManager::GetInstance().MousePress(1)){

        Shader::GetInstance().AddLight(InputManager::GetInstance().GetMouseX()/16,InputManager::GetInstance().GetMouseY()/16,133);
    }
    if (InputManager::GetInstance().MousePress(3)){
        Shader::GetInstance().AddBlock(InputManager::GetInstance().GetMouseX()/16,InputManager::GetInstance().GetMouseY()/16,255);
    }
    if (InputManager::GetInstance().KeyPress(SDLK_l)){
        Shader::GetInstance().ClearLights();
    }
    if (InputManager::GetInstance().KeyPress(SDLK_p)){
        for (int i=1;i<10;i++){
            while (!Shader::GetInstance().AddLight(rand()%40,rand()%30,133)){};
        }
    }


}
