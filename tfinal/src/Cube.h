#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "Point.h"

class Cube {
private:
    int l; // side lenght

    Point front[2][2];
    Point back[2][2];

    Point frontTransf[2][2];
    Point backTransf[2][2];

    float ang = 0;

public:
    Cube(int size, float x, float y, float z);

    void render();
    void transform();
};

#endif