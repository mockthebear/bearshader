#include "camera.hpp"
#include "inputmanager.hpp"

float Camera::speed = 0;
Rect Camera::pos(0,0,0,0);
Rect Camera::EffectArea(0,0,0,0);
Rect Camera::UpdateArea(0,0,0,0);
GameObject * Camera::focus = NULL;
int Camera::h = 0;
int Camera::w = 0;

void Camera::SetHW(int ww,int hh){

    h = hh;
    w = ww;
    pos.h = (h);
    pos.w = (w);
    EffectArea.h = h+EFFECT_ARE_RANGE*4;
    EffectArea.w = w+EFFECT_ARE_RANGE*4;
    UpdateArea.w = w+EFFECT_ARE_RANGE*2;
    UpdateArea.h = h+EFFECT_ARE_RANGE*2;
}
void Camera::Update(float dt){
    if (focus != NULL){
        //focus = Penguins::player;
        //int x = focus->getX();e
        if (focus->round){
            pos.x = (focus->ball.x+ focus->ball.r/2-pos.w/2);
            pos.y = (focus->ball.y+ focus->ball.r/2-pos.h/2);
        }else{
            pos.x = (focus->box.x+focus->box.w/2-pos.w/2);
            pos.y = (focus->box.y+focus->box.h/2-pos.h/2);

        }
        EffectArea.x = pos.x-EFFECT_ARE_RANGE*2;
        EffectArea.y = pos.y-EFFECT_ARE_RANGE*2;
        UpdateArea.x = pos.x-EFFECT_ARE_RANGE;
        UpdateArea.y = pos.y-EFFECT_ARE_RANGE;

    }else{
        float sx,sy;
        sx = sy = 0;
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
            sy = sy-speed;
        }
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
            sy = sy+speed;
        }
        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
            sx = sx-speed;
        }
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
            sx = sx+speed;
        }
        pos.y += sy*dt;
        pos.x += sx*dt;
        EffectArea.x = pos.x-EFFECT_ARE_RANGE*2;
        EffectArea.y = pos.y-EFFECT_ARE_RANGE*2;
        UpdateArea.x = pos.x-EFFECT_ARE_RANGE;
        UpdateArea.y = pos.y-EFFECT_ARE_RANGE;

    }
}

