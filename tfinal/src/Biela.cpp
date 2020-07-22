#include "Biela.h"

Biela::Biela(int length, Point center) : Object(center) {
    this->length = length;
}

void Biela::render() {
    color(0, 0, 1);
    line(pVirabrequim.getX(), pVirabrequim.getY(), pPistao.getX(), pPistao.getY());

    color(0, 1, 1);
    circle(pPistao.getX(), pPistao.getY(), 3, 10);
}

void Biela::transform() {
    // TODO
}

void Biela::connect(Point ptConnection, float ang) {
    Point p = ptConnection.copy();

    // move to origin
    p.translate(-center.getX(), -center.getY(), -center.getZ());

    p.rotateZ(angZ);
    p.rotateY(ang);
    p.rotateX(angX);

    p.translate(0, 0, 150);

    p.project(distance);

    // return back to the original center
    p.translate(center.getX(), center.getY(), center.getZ());

    // optional: centralizing in another point on screen
    p.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    pVirabrequim = p;

    float length = 80; //hipotenusa representa o comprimento da biela
    float xVirabrequim = ptConnection.getX();
    float yVirabrequim = ptConnection.getY();
    float cateto = sqrt(length * length - xVirabrequim * xVirabrequim); //pitagoras  hip^2 = cat^2 + cat^2
    float xPistao = 0;
    float yPistao = cateto + yVirabrequim;

    Point pTemp = Point(xPistao, yPistao, ptConnection.getZ());

    // move to origin
    pTemp.translate(-center.getX(), -center.getY(), -center.getZ());

    // pTemp.rotateZ(angZ);
    // pTemp.rotateY(angY);
    // pTemp.rotateX(angX);

    pTemp.translate(0, 0, 150); // cateto aqui

    pTemp.project(distance);

    // return back to the original center
    pTemp.translate(center.getX(), center.getY(), center.getZ());

    // optional: centralizing in another point on screen
    // sem cateto aqui
    pTemp.translate(translatePoint.getX(), pVirabrequim.getY() + cateto, translatePoint.getZ());

    pPistao = pTemp;

    // TODO: não pode deformar
    float d1 = sqrt(pow(pPistao.getX() - pVirabrequim.getX(), 2) + pow(pPistao.getY() - pVirabrequim.getY(), 2));
    printf("distance: %.1f\n", d1);
    // circle(xPistao + translatePoint.getX(), yPistao + translatePoint.getY(), 3, 10);
}

Point Biela::getConnectionPistao() {
    return pPistao;
    // projetar o ponto do pistao
    // ponto do virabrequim ja esta projetado
    // return Point(pVirabrequim.getX(), pVirabrequim.getY() + length, pVirabrequim.getZ());
}