


#ifndef TITLEH
#define TITLEH

#include "../state.hpp"
#include "../text.hpp"
#include "../inputmanager.hpp"
#include "../gamebase.hpp"
#include "../renderhelp.hpp"
#include "shader.hpp"
class Title: public State{
    public:
        Title();
        ~Title();
        void Update(float);
        void Render();
        void Input();
        void Begin(){};
        void AddObject(GameObject *o){};
        void AddCollision(GameObject *o){};
        void AddCreature(GameObject *o){};

    private:
        Text *blockSize_t,*TtoRender_t,*time_tt;
        Shader *lightSystem;
        int introStage;



};




#endif
