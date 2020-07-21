#ifndef CYLINDER_H_INCLUDED
#define CYLINDER_H_INCLUDED

#include "Object.h"

class Cylinder : public Object {

public:
    Cylinder(int r, int height, Point center);

    void render();
};

#endif
