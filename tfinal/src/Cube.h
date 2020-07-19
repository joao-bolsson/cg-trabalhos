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

    float angX = 0;
    float angY = 0;
    float angZ = 0;

    int distance = 70;

public:
    Cube(int size, float x, float y, float z);

    void render();
    void transform();
    void setDistance(int d);
    int getDistance();
    void setAngX(float ang);
    float getAngX();
    void setAngY(float ang);
    float getAngY();
    void setAngZ(float ang);
    float getAngZ();
};

#endif