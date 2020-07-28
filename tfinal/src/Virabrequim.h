#ifndef VIRABREQUIM_H_INCLUDED
#define VIRABREQUIM_H_INCLUDED

#include "Cylinder.h"

class Virabrequim : public Cylinder {
private:
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

    void transform();
    void render();

    /**
     * Returns the point to connect the biela. Not transformed (it's on origin)
     */
    Point getPtConnection();

    /**
     * Returns the connection point to connect the biela. Transformed point with rotation.
     */
    Point getPtConnectionTransf();
};

#endif
