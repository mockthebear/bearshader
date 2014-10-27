#include "geometry.hpp"
#include "object.hpp"
#include "definitions.hpp"
#include <stdio.h>
#ifndef CAMERAH
#define CAMERAH

class Camera{
    public:
        static Rect pos,EffectArea,UpdateArea;
        static float speed;
        static void Follow(GameObject *ob){focus = ob;};
        static void Unfollow(){focus = NULL;};
        static void Update(float dt);
        static void SetHW(int h,int w);
    private:
    static GameObject *focus;
    static int h,w;
};

#endif
