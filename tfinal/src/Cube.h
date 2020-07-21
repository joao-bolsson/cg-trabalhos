#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "Object.h"

class Cube : public Object {
private:
    int l; // side lenght

public:
    Cube(int size, Point center);

    void render();
};

#endif