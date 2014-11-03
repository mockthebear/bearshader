#include "block.hpp"

Block::Block(int x,int y,int bl){
    box.x = x;
    box.y = y;
    box.h = 16;
    box.w = 16;
    setRotation(0);
    solid = true;
    call = false;
    UID = (uint64_t)this;
    spr = new Sprite("img/block.png");
}
Block::~Block(){

}
void Block::Update(float dt){

}
void Block::Render(){
    spr->Render(box.x-Camera::pos.x,box.y-Camera::pos.y);
}
bool Block::IsDead(){
    return false;
};
bool Block::IsInScreen(Point& p){
    return true;
}
void Block::NotifyCollision(GameObject *p){

}
bool Block::Is(int p){
    return p == OBJ_MAPITEM;
}

