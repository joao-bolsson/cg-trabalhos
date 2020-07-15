#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "Point.h"
#include <math.h>
#define PI 3.14159265359
#define FACTOR_RAD 6
#define DIMX (FACTOR_RAD * 2 + 1)
#define DIMY (FACTOR_RAD + 1)

class Sphere {
private:
    float radius;
    float ang = 0;

    Point mat[DIMX][DIMY];
    Point transf[DIMX][DIMY];

public:
    Sphere(float radius);

    void transform();
    Point translate(Point p);
    Point project(Point p);
    Point rotateX(Point p);

    void render();
};

#endif
