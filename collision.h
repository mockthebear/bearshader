#include <cmath>
#include <algorithm>

// Substitua isso pelo(s) header(s) da(s) sua(s) classe(s) de geometria criadas no E1
#include "geometry.hpp"

// Essa é uma implementação do SAT feita pelo Lucas Neves.
// Recebe dois Rects e suas rotações, e detecta se os retângulos colidem.
// Mais informações sobre o método podem ser encontradas nos seguintes links:
// http://www.metanetsoftware.com/technique/tutorialA.html
// http://www.gamedev.net/page/resources/_/technical/game-programming/2d-rotated-rectangle-collision-r2604
#ifndef COLH
#define COLH
class Collision {

    public:
        static inline bool IsColliding( Rect& b,Circle& a ){
            //Closest point on collision box
            int cX, cY;
            //Find closest x offset
            if( a.x < b.x )
            {
                cX = b.x;
            }
            else if( a.x > b.x + b.w )
            {
                cX = b.x + b.w;
            }
            else
            {
                cX = a.x;
            }

            //Find closest y offset
            if( a.y < b.y )
            {
                cY = b.y;
            }
            else if( a.y > b.y + b.h )
            {
                cY = b.y + b.h;
            }
            else
            {
                cY = a.y;
            }

            //If the closest point is inside the circle
            if( distanceSquared( a.x, a.y, cX, cY ) < a.r * a.r )
            {
                //This box and the circle have collided
                return true;
            }

            //If the shapes have not collided
            return false;
        };

        static inline bool IsColliding(Rect& a,  Rect& b){
            //The sides of the rectangles
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;

            //Calculate the sides of rect A
            leftA = a.x;
            rightA = a.x + a.w;
            topA = a.y;
            bottomA = a.y + a.h;

            //Calculate the sides of rect B
            leftB = b.x;
            rightB = b.x + b.w;
            topB = b.y;
            bottomB = b.y + b.h;

            //If any of the sides from A are outside of B
            if( bottomA <= topB )
            {
                return false;
            }

            if( topA >= bottomB )
            {
                return false;
            }

            if( rightA <= leftB )
            {
                return false;
            }

            if( leftA >= rightB )
            {
                return false;
            }

            //If none of the sides from A are outside B
            return true;
        };

        static inline bool IsColliding(Rect& a,  Rect& b, float angleOfA, float angleOfB) {
            Point A[] = { Point( a.x, a.y + a.h ),
                          Point( a.x + a.w, a.y + a.h ),
                          Point( a.x + a.w, a.y ),
                          Point( a.x, a.y )
                        };
            Point B[] = { Point( b.x, b.y + b.h ),
                          Point( b.x + b.w, b.y + b.h ),
                          Point( b.x + b.w, b.y ),
                          Point( b.x, b.y )
                        };

            for (auto& v : A) {
                v = Rotate(v - a.GetCenter(), angleOfA) + a.GetCenter();
            }

            for (auto& v : B) {
                v = Rotate(v - b.GetCenter(), angleOfB) + b.GetCenter();
            }

            Point axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

            for (auto& axis : axes) {
                float P[4];

                for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

                float minA = *std::min_element(P, P + 4);
                float maxA = *std::max_element(P, P + 4);

                for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

                float minB = *std::min_element(P, P + 4);
                float maxB = *std::max_element(P, P + 4);

                if (maxA <= minB || minA >= maxB)
                    return false;
            }

            return true;
        }

    private:
        static inline double distanceSquared( int x1, int y1, int x2, int y2 )
        {
            int deltaX = x2 - x1;
            int deltaY = y2 - y1;
            return deltaX*deltaX + deltaY*deltaY;
        }
        static inline float Mag(const Point& p) {
            return std::sqrt(p.x * p.x + p.y * p.y);
        }

        static inline Point Norm(const Point& p) {
            return p * (1.f / Mag(p));
        }

        static inline float Dot(const Point& a, const Point& b) {
            return a.x * b.x + a.y * b.y;
        }

        static inline Point Rotate(const Point& p, float angle) {
            float cs = std::cos(angle), sn = std::sin(angle);
            return Point ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
        }
};

#endif
// Aqui estão dois operadores que sua classe Point deve precisar, se já não tiver.
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Point operator+(const Point& rhs) const {
//    return Point(x + rhs.x, y + rhs.y);
// }

// Point operator-(const Point& rhs) const {
//    return Point(x - rhs.x, y - rhs.y);
// }
