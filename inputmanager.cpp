#include "inputmanager.hpp"
#include "gamebase.hpp"
#include "configmanager.hpp"
#include <stdio.h>
#include <stdlib.h>     /* abs */
#include <iostream>

//#define JOYSTICK_USE
void KeyBind::SetKey(int i,int k){
        switch (i){
            case 0:
                K_UP = k;
                break;
            case 1:
                K_DOWN = k;
                break;
            case 2:
                K_LEFT = k;
                break;
            case 3:
                K_RIGHT = k;
                break;
            case 4:
                K_ATTACK = k;
                break;
            case 6:
                K_ACTION = k;
                break;
            case 7:
                K_ACTION2 = k;
                break;
            case 5:
                K_MAGIC = k;
                break;
            case 8:
                K_TOGGLEWEAPON = k;
                break;
            case 9:
                K_TOOGLEMAGIC = k;
                break;
            case 10:
                K_INVENTORY = k;
                break;
            case 11:
                K_EXIT = k;
                break;
            case 12:
                K_MAP = k;
                break;
            case 13:
                K_GRAB = k;
                break;
        }
}
bool KeyBind::CanSetKey(int i,int k){
    if (K_UP == k and i != 0)
        return false;
    if (K_DOWN == k and i != 1)
        return false;
    if (K_LEFT == k and i != 2)
        return false;
    if (K_RIGHT == k and i != 3)
        return false;
    if (K_ATTACK == k and i != 4)
        return false;
    if (K_ACTION == k and i != 5)
        return false;
    if (K_ACTION2 == k and i != 6)
        return false;
    if (K_MAGIC == k and i != 7)
        return false;
    if (K_TOGGLEWEAPON == k and i != 8)
        return false;
    if (K_TOOGLEMAGIC == k and i != 9)
        return false;
    if (K_INVENTORY == k and i != 10)
        return false;
    if (K_EXIT == k and i != 11)
        return false;
    if (K_MAP == k and i != 12)
        return false;
    if (K_GRAB == k and i != 13)
        return false;
    return true;
}
KeyBind::KeyBind(){
    LoadKeyboard();
      MOUSESPEED      = 30.0f;
}
void KeyBind::LoadKeyboard(){

    K_UP            = SDLK_w;       //0
    K_DOWN          = SDLK_s;       //1
    K_LEFT          = SDLK_a;       //2
    K_RIGHT         = SDLK_d;       //3
    K_ATTACK        = SDLK_UP;
    K_ACTION        = SDLK_DOWN;
    K_ACTION2       = SDLK_RIGHT;
    K_MAGIC         = SDLK_LEFT;
    K_TOGGLEWEAPON  = SDLK_q;
    K_TOOGLEMAGIC   = SDLK_e;
    K_INVENTORY     = SDLK_i;
    K_EXIT          = SDLK_ESCAPE;
    K_MAP           = SDLK_TAB;
    K_GRAB          = SDLK_SPACE;
}
void KeyBind::LoadJoystick(){

    K_UP            = 1001;
    K_DOWN          = 1003;
    K_LEFT          = 1004;
    K_RIGHT         = 1002;
    K_ATTACK        = 1012;
    K_ACTION        = 1010;
    K_ACTION2       = 1011;
    K_MAGIC         = 1013;
    K_TOGGLEWEAPON  = 1014;
    K_TOOGLEMAGIC   = 1015;
    K_INVENTORY     = 1019;
    K_EXIT          = 1018;
    K_MAP           = 1016;
    K_GRAB          = 1017;


}
InputManager::InputManager(){
    mode = INPUT_KEYBOARD;
    for (int i=0;i<=N_MOUSE_BUTTONS;i++){
        mouseState[i] = RELEASED;
    }
    quitGame = false;
}
InputManager::~InputManager(){
    std::cout << "Closed inputmanager\n";
    for (int i=0;i<joycount;i++){
        //SDL_JoystickClose(joysticks[i]);
    }

}

void InputManager::InitJoySticks(){
    const char *name;
    printf("There are %d joysticks attached\n", SDL_NumJoysticks());
    joycount = SDL_NumJoysticks();
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        name = SDL_JoystickNameForIndex(i);
        printf("Joystick %d: %s\n", i, name ? name : "Unknown Joystick");
        joysticks[i] = SDL_JoystickOpen(i);
        if (joysticks[i] == NULL) {
            std::cout << "SDL_JoystickOpen(%d) failed: %s\n" <<  SDL_GetError();
        } else {
            char guid[64];
            SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(joysticks[i]), guid, sizeof (guid));
            printf("       axes: %d\n", SDL_JoystickNumAxes(joysticks[i]));
            printf("      balls: %d\n", SDL_JoystickNumBalls(joysticks[i]));
            printf("       hats: %d\n", SDL_JoystickNumHats(joysticks[i]));
            printf("    buttons: %d\n", SDL_JoystickNumButtons(joysticks[i]));
            printf("instance id: %d\n", SDL_JoystickInstanceID(joysticks[i]));
            printf("       guid: %s\n", guid);
            //joystick);
        }
    }

}

InputManager& InputManager::GetInstance(){
    static InputManager teste;
    return teste;
}
void InputManager::CallActive(int i,InputState s){
    for (auto &it: Hooks){
        it.second(i,s);
    }
}
void InputManager::Update(){
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    for ( auto it = keyState.begin(); it != keyState.end(); ++it ){
          if (it->second == JUST_PRESSED){
                it->second = PRESSED;
            }
        if (it->second == JUST_RELEASED){
                it->second = RELEASED;
            }
    }
    for ( int i=0;i<3;i++ ){
          if (mouseState[i] == JUST_PRESSED){
                mouseState[i] = PRESSED;
          }
          if (mouseState[i] == JUST_RELEASED){
                mouseState[i] = RELEASED;
          }
    }
   while (SDL_PollEvent(&event)) {


        if(event.type == SDL_WINDOWEVENT){
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){}
                ConfigManager::GetInstance().Resize();
            if(event.window.event == SDL_WINDOWEVENT_CLOSE){
                Game::instance->isClosing = true;
                std::cout << "Signal to stop!\n";
            }



        }
        if(event.type == SDL_QUIT) {
            quitGame = true;
        }

        if (event.type == SDL_KEYDOWN){
                //printf("Apertado tecla %d\n",event.key.keysym.sym);
                if (keyState[event.key.keysym.sym] != PRESSED){
                    keyState[event.key.keysym.sym] = JUST_PRESSED;
                    CallActive(event.key.keysym.sym,JUST_PRESSED);
                }
        }
        if (event.type == SDL_KEYUP){
                if (keyState[event.key.keysym.sym] != RELEASED){
                    keyState[event.key.keysym.sym] = JUST_RELEASED;
                    CallActive(event.key.keysym.sym,JUST_RELEASED);
                }
        }
        //Mouse
        if (event.type == SDL_MOUSEBUTTONDOWN){
            if (mouseState[event.button.button] != PRESSED){
                mouseState[event.button.button] = JUST_PRESSED;
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP){
            if (mouseState[event.button.button] != RELEASED){
                mouseState[event.button.button] = JUST_RELEASED;
            }
        }


        switch(event.type){

            case SDL_JOYAXISMOTION:{

                if ( abs( (int)event.jaxis.value) > 28700 ){
                    //Realmente apertou!
                    if (event.jaxis.value < 0){
                        if (event.jaxis.axis == 0){
                            if (keyState[1004] != PRESSED){
                                keyState[1004] = JUST_PRESSED;
                                CallActive(1004,JUST_PRESSED);
                            }
                       }else{
                            if (keyState[1001] != PRESSED){
                                keyState[1001] = JUST_PRESSED;
                                CallActive(1001,JUST_PRESSED);
                            }
                       }
                    }else{
                        if (event.jaxis.axis == 0){
                            if (keyState[1002] != PRESSED){
                                keyState[1002] = JUST_PRESSED;
                                CallActive(1002,JUST_PRESSED);
                            }
                        }else{
                            if (keyState[1003] != PRESSED){
                                keyState[1003] = JUST_PRESSED;
                                CallActive(1003,JUST_PRESSED);
                            }
                        }
                    }

                }else{
                    if (event.jaxis.axis == 0){
                        keyState[1002] = JUST_RELEASED;
                        keyState[1004] = JUST_RELEASED;
                        CallActive(1004,JUST_RELEASED);
                        CallActive(1002,JUST_RELEASED);
                    }else{
                        keyState[1001] = JUST_RELEASED;
                        keyState[1003] = JUST_RELEASED;
                        CallActive(1003,JUST_RELEASED);
                        CallActive(1001,JUST_RELEASED);
                    }

                }

                break;
                }
            case SDL_JOYHATMOTION:
                if (event.jhat.value == SDL_HAT_CENTERED)
                    for (int k=1;k<5;k++)
                        if (keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + k ] != RELEASED){
                            keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + k ] = JUST_RELEASED;
                        }
                if (event.jhat.value & SDL_HAT_UP)
                    if (keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + 1 ] != PRESSED){
                        keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + 1 ] = JUST_PRESSED;
                    }
                if (event.jhat.value & SDL_HAT_RIGHT)
                    if (keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + 2 ] != PRESSED){

                        keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + 2 ] = JUST_PRESSED;
                    }
                if (event.jhat.value & SDL_HAT_DOWN)
                    if (keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + 3 ] != PRESSED){

                        keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + 3 ] = JUST_PRESSED;
                    }
                if (event.jhat.value & SDL_HAT_LEFT)
                    if (keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + 4 ] != PRESSED){

                        keyState[1000 + 100*event.jbutton.which + 30 *  event.jhat.hat + 4 ] = JUST_PRESSED;
                    }
                break;
            case SDL_JOYBALLMOTION:
                printf("Joystick %d ball %d delta: (%d,%d)\n",
                       event.jball.which,
                       event.jball.ball, event.jball.xrel, event.jball.yrel);
                break;
            case SDL_JOYBUTTONDOWN:
                if (keyState[1000 + 100*event.jbutton.which + 10 +  event.jbutton.button] != PRESSED){
                    keyState[1000 + 100*event.jbutton.which + 10 +  event.jbutton.button] = JUST_PRESSED;
                    CallActive(1000 + 100*event.jbutton.which + 10 +  event.jbutton.button,JUST_PRESSED);

                }
                break;
            case SDL_JOYBUTTONUP:
                if (keyState[1000 + 100*event.jbutton.which + 10 +  event.jbutton.button] != RELEASED){
                    keyState[1000 + 100*event.jbutton.which + 10 +  event.jbutton.button] = JUST_RELEASED;
                    CallActive(1000 + 100*event.jbutton.which + 10 +  event.jbutton.button,JUST_RELEASED);


                }
                break;
            case 1541:{
                printf("Joy conencted!\n");
                printf("There are %d joysticks attached\n", SDL_NumJoysticks());
                if (joycount != SDL_NumJoysticks()){
                     for (int i = 0; i < SDL_NumJoysticks(); ++i) {
                        printf("Joystick %d: %s\n", i, SDL_JoystickNameForIndex(i) ? SDL_JoystickNameForIndex(i) : "Unknown Joystick");
                        joysticks[i] = SDL_JoystickOpen(i);
                        if (joysticks[i] == NULL) {
                            std::cout << "SDL_JoystickOpen(%d) failed: %s\n" <<  SDL_GetError();
                        }
                    }
                }
            }
            case 1542:{
                printf("Joy disconencted!\n");
                printf("There are %d joysticks attached\n", SDL_NumJoysticks());
            }
                /* Fall through to signal quit */
        }

    }
    //std::cout << SDL_NumJoysticks() << "\n";

}

bool InputManager::IsAnyKeyPressed(){

    return
    keyState[binds.K_ACTION2] == JUST_PRESSED or keyState[binds.K_ACTION] == JUST_PRESSED or keyState[binds.K_ATTACK] == JUST_PRESSED or keyState[binds.K_MAGIC] == JUST_PRESSED
    or keyState[binds.K_UP] == JUST_PRESSED or keyState[binds.K_DOWN] == JUST_PRESSED or keyState[binds.K_LEFT] == JUST_PRESSED or keyState[binds.K_RIGHT] == JUST_PRESSED
    or keyState[binds.K_INVENTORY] == JUST_PRESSED or keyState[binds.K_MAP] == JUST_PRESSED or keyState[binds.K_EXIT] == JUST_PRESSED or keyState[binds.K_GRAB] == JUST_PRESSED;
}

int InputManager::GetMouseX(){
    return (mouseX/ConfigManager::GetInstance().ScaleRatioW()) - (  ConfigManager::GetInstance().OffsetW()/2.0);};
int InputManager::GetMouseY(){
    return mouseY/ConfigManager::GetInstance().ScaleRatioH();};
bool InputManager::KeyPress(int key){
    return keyState[key] == JUST_PRESSED;
}

bool InputManager::KeyRelease(int key){
    return keyState[key] == JUST_RELEASED;
}
bool InputManager::MousePress(int key){
    return mouseState[key] == JUST_PRESSED;
}
bool InputManager::MouseRelease(int key){
    return mouseState[key] == JUST_RELEASED;
}
bool InputManager::IsKeyDown(int key){
    return keyState[key] == JUST_PRESSED or keyState[key] == PRESSED;
}

bool InputManager::IsMousePressed(int key){
    return mouseState[key] == JUST_PRESSED or mouseState[key] == PRESSED;
}
