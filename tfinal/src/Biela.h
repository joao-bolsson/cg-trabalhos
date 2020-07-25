#ifndef BIELA_H_INCLUDED
#define BIELA_H_INCLUDED

#include "Object.h"

class Biela : public Object {
private:
    Point pVirabrequim;  // ponto conexão virabrequim -> biela
    Point pPistao;       // ponto conexão pistao -> biela
    Point pPistaoTransf; // ponto conexão pistao -> biela (transformado)
    int length;

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
    void connect(Point ptConnection, float ang);

    /**
     * Point to conect the pistao. 
     */
    Point getConnectionPistao();
};

#endif