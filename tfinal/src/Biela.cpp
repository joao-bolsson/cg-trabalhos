#include "Biela.h"

Biela::Biela(int length, Point center) : Object(center) {
    this->length = length;
}

void Biela::render() {
    color(0, 0, 1);
    line(pVirabrequim.getX(), pVirabrequim.getY(), pPistaoTransf.getX(), pPistaoTransf.getY());
}

void Biela::transform() {
    // TODO
}

void Biela::connect(Point ptConnection, float ang) {
    //// dois pontos para checar se a biela deforma ou nao
    Point pViraTest, pPistaoTest;

    // recebe o ponto de conexão com o virabrequim e transforma
    Point p = ptConnection.copy();

    // move to origin
    p.translate(-center.getX(), -center.getY(), -center.getZ());

    p.rotateZ(angZ);
    p.rotateY(angY);
    p.rotateX(angX);

    pViraTest = p.copy();
    pViraTest.translate(center.getX(), center.getY(), center.getZ());

    p.translate(0, 0, 150);

    p.project(distance);

    // return back to the original center
    p.translate(center.getX(), center.getY(), center.getZ());

    // centralizing in another point on screen
    p.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    pVirabrequim = p;

    // calcula o ponto de conexão com o pistao  /// esta fazendo a mesma coisa q o pViraTest
    Point pConTemp = ptConnection.copy();
    pConTemp.translate(-center.getX(), -center.getY(), -center.getZ());

    pConTemp.rotateZ(angZ);
    pConTemp.rotateY(angY);
    pConTemp.rotateX(angX);

    pConTemp.translate(center.getX(), center.getY(), center.getZ());

    float xVirabrequim = pConTemp.getX();
    float yVirabrequim = pConTemp.getY();
    float cateto = sqrt(length * length - xVirabrequim * xVirabrequim);

    float xPistao = center.getX(); // 0
    float yPistao = cateto + yVirabrequim;

    Point pTemp = Point(xPistao, yPistao, pConTemp.getZ());
    pPistao = pTemp.copy();

    pTemp.translate(0, 0, 150);

    pTemp.project(distance);

    pTemp.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    pPistaoTransf = pTemp;

    // pPistaoTransf
    // TODO: não pode deformar
    float d1 = sqrt(pow(pPistao.getX() - pViraTest.getX(), 2) + pow(pPistao.getY() - pViraTest.getY(), 2) + pow(pPistao.getZ() - pViraTest.getZ(), 2));
    printf("distance: %.1f\n", d1);
}

Point Biela::getConnectionPistao() {
    return pPistao;
}