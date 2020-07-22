#ifndef PISTAO_H_INCLUDED
#define PISTAO_H_INCLUDED

#include "Object.h"

class Pistao : public Object {
private:
    Point ptVira;           // ponto do virabrequim conexão com a biela
    Point ptViraCenter;     // centro do virabrequim
    Point ptConnection;     // ponto do pistao -> biela
    Point ptConTransformed; // ponto do pistao -> biela (transformado)
    int radius;
    int length;
    float bielaLength;

public:
    Pistao(Point center, Point ptVira,
           Point ptViraCenter,
           int radius,
           int length,
           float bielaLength);

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
