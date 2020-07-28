#ifndef PISTAO_H_INCLUDED
#define PISTAO_H_INCLUDED

#include "Cylinder.h"

class Pistao : public Cylinder {
private:
    Point pBiela;          // ponto conexão pistao -> biela
    Point pConectionBiela; // ponto conexão pistao -> biela (sem transformações)

public:
    Pistao(int radius, int length, Point center);

    void render();
    void transform();

    /**
     * Connect this object with the given point.
     *    
     * @param  ptConnection: Point to connect with.
     */
    void connect(Point ptConnection);
};

#endif
