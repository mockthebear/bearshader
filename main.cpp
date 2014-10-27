#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "gamebase.hpp"
#include "configmanager.hpp"

Game *game = NULL;
int main (int argc, char** argv) {
 game = new Game((char*)"Jogo",ConfigManager::GetInstance().GetScreenW(),ConfigManager::GetInstance().GetScreenH());
    game->Run();
    delete game;
    return 0;

}
