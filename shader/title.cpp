#include "title.hpp"


Title::Title(){

    requestQuit = requestDelete = false;
    introStage = 1;
}



Title::~Title(){


    std::cout << "Closed title\n";
}


void Title::Update(float dt){
    Input();

}


void Title::Render(){
    static int cycle = 0;
    cycle++;
    SDL_SetRenderDrawColor(Game::instance->GetRenderer(), 0, 0,0, 0);
    SDL_RenderClear( Game::instance->GetRenderer() );
    for (int y=0;y<15;y++)
        for (int x=0;x<20;x++)
            RenderHelp::DrawSquareColorA(32*x,32*y,32,32,255,0,0,cycle%255);



}
void Title::Input(){
    KeyBind *bind = InputManager::GetInstance().GetKeyBinds();
    if (InputManager::GetInstance().ShouldQuit()){
        requestQuit = true;
    }

}
