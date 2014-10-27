#include "state.hpp"

State::State(){
    requestDelete = requestQuit = false;
}
void State::AddObject(GameObject* p){
    ObjectArray.emplace_back(p);

}

void State::AddCollision(GameObject* p){
    CollisionArray.emplace_back(p);

}

void State::AUXAddCollision(GameObject* p){
    auxCollisionArray.emplace_back(p);

}
void State::AddCreature(GameObject* p){
    CreatureArray.emplace_back(p);

}

void State::AddEffect(GameObject* p){
   EffectArray.emplace_back(p);

}
