#ifndef PISTAO_H_INCLUDED
#define PISTAO_H_INCLUDED

#include "Cylinder.h"

class Pistao : public Cylinder {
private:
    Point pBiela;          // ponto conexão pistao -> biela
    Point pConectionBiela; // ponto conexão pistao -> biela (sem transformações)
    Cylinder *camisa;

public:
    /**
     * Creates a virabrequim.
     * 
     * @param  radius: Cylinder radius.
     * @param  length: Cylinder length.
     * @param  viraLength: Virabrequim length.
     * @param  center: Origin.
     */
    Pistao(int radius, int length, int viraLength, Point center);

    void render();
    void renderCamisa();
    void transform();

    void rotate(double angX, double angY, double angZ);
    void setDistance(int d);

    /**
     * Connect this object with the given point.

     * * @param  ptConnection: Point to connect with.
     */
    void connect(Point ptConnection);

    /**
     * Translates the 'camisa' to the given point.
     *  
     * @param  p: Point to translate.
     */
    void connectCamisa(Point p);
};

#endif
