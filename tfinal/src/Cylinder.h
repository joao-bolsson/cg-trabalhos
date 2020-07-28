#ifndef CYLINDER_H_INCLUDED
#define CYLINDER_H_INCLUDED

#include "Object.h"

class Cylinder : public Object {

protected:
    int radius; // radius inside of cylinder
    int length; // cylinder length

public:
    Cylinder(int r, int length, Point center, bool vertical = true);
    int getLength();

    void render();
};

#endif
