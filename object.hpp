#ifndef OBJH
#define OBJH

#include "geometry.hpp"
#include <string>

enum ObjType{
    OBJ_NULL=0,
    //system
    OBJ_STILLANIMATION,
    OBJ_ANIMATEDTEXT,
    OBJ_CREATURE,
    OBJ_MONSTER,
    //Blocks
    OBJ_COLLISION,
    OBJ_COLLISIONT,
    OBJ_COLLISIONTT,
    OBJ_ACTIONBLOCK,

    //Item
    OBJ_MAPITEM,
    OBJ_ITEM,
    OBJ_POTION,
    OBJ_COIN,
    OBJ_BOX,
    OBJ_MAPBOX,

    //Creatures
    OBJ_PLAYER,
    OBJ_SPIDER,
    OBJ_RANGED,
    OBJ_PROJECTILE,
    OBJ_BOSS,

    //Blegh
    OBJ_END,
};
class GameObject{
    public:
    virtual void Update(float)=0;
    virtual ~GameObject(){};
    virtual void Render()=0;
    virtual bool IsDead()=0;
    virtual bool IsInScreen(Point& p)=0;
    virtual void NotifyCollision(GameObject *p)=0;
    virtual bool Is(int)=0;
    //virtual void NotifyDamage(GameObject *bj,int n)=0;
    float getRotation(){return rotation;};
    void setRotation(float n){rotation= n;};
    uint64_t getUid(){return UID;};
    Rect box;
    Circle ball;
    bool round,solid,call;
    protected:
        float rotation;
        uint64_t Flags;
        uint64_t UID;



};

#endif
