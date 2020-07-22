#ifndef VIRABREQUIM_H_INCLUDED
#define VIRABREQUIM_H_INCLUDED

#include "Object.h"

class Virabrequim : public Object {
private:
    int radius;             // radius inside of cylinder
    int length;             // cylinder length
    Point ptConnection;     // ponto para conectar a biela
    Point ptConTransformed; // ponto para conectar a biela

public:
    Virabrequim(int radius, int length, Point center);

    void transform();
    void render();

    Point getPtConnection();
    Point getPtConnectionTransf();
};

#endif
