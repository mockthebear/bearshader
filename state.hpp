#include "object.hpp"
#include "sprite.hpp"

#ifndef STATEH
#define STATEH

#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
#include <list>



class State{
    public:
        State();
        virtual ~State(){};
        virtual void Update(float dt) =0;
        virtual void Render() =0;
        virtual void Begin() =0;
        virtual void AddObject(GameObject *b);
        virtual void AddCollision(GameObject *b);
        virtual void AUXAddCollision(GameObject *b);
        virtual void AddCreature(GameObject *b);
        virtual void AddEffect(GameObject *b);
        bool RequestedDeleted(){return requestDelete;};
        bool RequestedQuit(){return requestQuit;};
        bool requestDelete,requestQuit;
        void SaveAt(std::string str){};
        std::vector<std::unique_ptr<GameObject>>* getCollisionArray(){return &CollisionArray;};
        std::vector<std::unique_ptr<GameObject>>* getCreatureArray(){return &CreatureArray;};
        std::vector<std::unique_ptr<GameObject>>* getEffectArray(){return &EffectArray;};

        int STATEID;
        int CanLoad,CanSave;
        int nd0,nd1,nd2;
        int lastLoad,lastSave;

        bool gameStarted;

        Point positions[5];
    protected:
        std::vector<std::unique_ptr<GameObject>> ObjectArray,CollisionArray,CreatureArray,EffectArray;
        std::vector<std::unique_ptr<GameObject>> auxCollisionArray;

        Sprite *bg;
        float dlbg;
        int pos;

};
#endif // STATEH
