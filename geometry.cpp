#include "geometry.hpp"
#include <math.h>
Rect::Rect(float xx,float yy,float hh,float ww){
    x = xx;
    y = yy;
    h = hh;
    w = ww;
}
Rect::Rect(){
    x = y =h = w =0;
}
Point Rect::GetCenter(){
    return Point(x+(w/2.0),y+(h/2.0));
}
bool Rect::IsInside(float xa,float ya){
    return xa <= x and xa >= x+w;
}


bool Rect::IsInside(Rect *r){
    Point p = r->GetCenter();
    //printf("%f - %f\n",x,w);
    return p.x >= x and p.x <= x+w and p.y >= y and p.y <= y+h;
}
Circle::Circle(float xx,float yy,float rr){
    x = xx;
    y = yy;
    r = rr;
}
Circle::Circle(){
    x = y = r = 0;
}

void Rect::Sum(float n){
    x = x+n;
    y = y+n;
    h = h+n;
    w = w+n;
}

Point::Point(float a,float b){
    x = a;
    y = b;
}
Point::Point(){
    x = y = 0;
}

float Point::getDistance(Point *p){
    return sqrt(pow((x - p->x),2.0) + pow((y-p->y),2.0));
}

