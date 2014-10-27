#ifndef GEOMH
#define GEOMH
#include <math.h>
#include <stdio.h>
class Point{
    public:
        Point();
        Point(float,float);
        float getDistance(Point *p);
        Point operator+(const Point& rhs) const {
           return Point(x + rhs.x, y + rhs.y);
        }
        Point operator-(const Point& rhs) const {
            return Point(x - rhs.x, y - rhs.y);
         }
         Point operator*(float f) const {
            return Point(x*f,y*f);
         }
         float x,y;

};


class Rect{
    public:
        Rect(float,float,float,float);
        Rect();
        float getXCenter(){return x+w/2;};
        float getYCenter(){return y+h/2;};
        bool IsInside(float xx,float yy);
        bool IsInside(Rect *r);
        void Sum(float n);
        Point GetCenter();
        float x,y,h,w;

};

class Circle{
    public:
        Circle(float,float,float);
        Circle();
        float x,y,r;
};

#endif
