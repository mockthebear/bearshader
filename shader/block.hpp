#ifndef aBLOCKH
#define aBLOCKH

#include "../object.hpp"
#include "../renderhelp.hpp"
#include "../sprite.hpp"
#include "../camera.hpp"


class Block: public GameObject{
    public:
        Block(int x,int y,int);
        ~Block();
        void Update(float);
        void Render();
        bool IsDead();
        bool IsInScreen(Point& p);
        void NotifyDamage(GameObject *bj,int n){};
        void NotifyCollision(GameObject *p);
        bool Is(int);
    private:
        Sprite *spr;
};


#endif // BLOCKH
