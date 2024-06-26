#ifndef BIELA_H_INCLUDED
#define BIELA_H_INCLUDED

#include "Cylinder.h"

class Biela : public Cylinder {
private:
    Point pConectionVira; // ponto conexão virabrequim -> biela (sem transformações)
    Point pVirabrequim;   // ponto conexão virabrequim -> biela
    Point pPistao;        // ponto conexão pistao -> biela
    Point pPistaoTransf;  // ponto conexão pistao -> biela (transformado)

public:
    Biela(int radius, int length, Point center);

    void render();
    void transform();

    /**
     * Connect this object with the given point and inclinates it in x axis.
     *    
     * @param  ptConnection: Point to connect with the virabrequim.
     * @param  ang: Inclination angle.
     */
    void connect(Point ptConnection, double ang);

    /**
     * Point to conect the pistao. 
     */
    Point getConnectionPistao();

    /**
     * Transformed point to conect the pistao. 
     */
    Point getConnectionPistaoTranf();
};

#endif