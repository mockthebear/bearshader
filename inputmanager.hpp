#ifndef INPUH
#define INPUH
#define N_MOUSE_BUTTONS 3
#include <SDL2/SDL.h>
#include "geometry.hpp"
#include <unordered_map>
#include <map>
#include <functional>


#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT


class KeyBind{
    public:
    KeyBind();
    int K_UP,K_DOWN,K_LEFT,K_RIGHT,K_ATTACK,K_ACTION,K_ACTION2,K_TOGGLEWEAPON,K_TOOGLEMAGIC,K_MAGIC,K_INVENTORY,K_EXIT,K_MAP,K_GRAB;
    float MOUSESPEED;
    bool CanSetKey(int i,int k);
    void SetKey(int i,int k);
    void LoadKeyboard();
    void LoadJoystick();
};

enum InputState{
            RELEASED=0,
            JUST_RELEASED,
            PRESSED,
            JUST_PRESSED
        };

enum InputMode{
    INPUT_KEYBOARD,
    INPUT_JOYSTICK,
};
class InputManager{
    public:
        void Update();
        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);
        bool MousePress(int key);
        bool MouseRelease(int key);
        bool IsMousePressed(int key);
        int GetMouseX();
        int GetMouseY();
        bool IsMouseInside (Rect rect);
        bool IsAnyKeyPressed();
        bool ShouldQuit (){return quitGame;};
        static InputManager& GetInstance();
        void InitJoySticks();
        InputManager();
        ~InputManager();
        KeyBind *GetKeyBinds(){return &binds;};
        void InsertHookFunction(int i,std::function<void (int , InputState)> F){ Hooks[i] = F; };
        void InsertEraseFunction(int i){ Hooks.erase(i); };

    private:
        InputMode mode;
        void CallActive(int i,InputState s);
        bool quitGame=false;
        int mouseX;
        int mouseY;
        SDL_JoyButtonEvent jooj;
        KeyBind binds;
        InputState mouseState[N_MOUSE_BUTTONS+1];
        SDL_Joystick *joysticks[4];
        SDL_Joystick *current;
        int joycount;
        std::unordered_map<int, InputState> keyState;
        std::map<int, std::function<void (int , InputState)> > Hooks;
};
#endif
