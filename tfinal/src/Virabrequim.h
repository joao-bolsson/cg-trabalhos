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
    /**
     * Creates a virabrequim. 
     *   
     * @param  radius: Cylinder radius.
     * @param  length: Virabrequim length.
     * @param  center: Point where it will be constructed.
     */
    Virabrequim(int radius, int length, Point center);

    int getLength();

    void transform();
    void render();

    Point getPtConnection();
    Point getPtConnectionTransf();
};

#endif
