#include "Biela.h"

Biela::Biela(int radius, int length, Point center) : Cylinder(radius, length, center) {
    // empty
}

void Biela::render() {
    if (1 > 2) { // desenha 2d
        color(0, 0, 1);
        line(pVirabrequim.getX(), pVirabrequim.getY(), pPistaoTransf.getX(), pPistaoTransf.getY());

        color(1, 0, 0);
        circle(pVirabrequim.getX(), pVirabrequim.getY(), 3, 10);

        color(0, 1, 0);
        circle(pPistaoTransf.getX(), pPistaoTransf.getY(), 3, 10);
        return;
    }
    Cylinder::render();
}

void Biela::transform() {
    // projeta o ponto do virabrequim
    Point p = pConectionVira.copy();
    p.translate(0, 0, 150);
    p.project(distance);

    Point pViraTranslate = Point(translatePoint.getX() - p.getX(), translatePoint.getY() - p.getY(), translatePoint.getZ());

    p.translate(pViraTranslate);

    pVirabrequim = p;

    // projeta o ponto do pistão
    Point pTemp = pPistao.copy();
    // translada para a origem
    pTemp.translate(-pConectionVira.getX(), -pConectionVira.getY(), -pConectionVira.getZ());
    // projeta
    pTemp.translate(0, 0, 150);
    pTemp.project(distance);

    // mostra no ponto da tela desejado
    pTemp.translate(translatePoint);

    pPistaoTransf = pTemp;

    // não pode deformar
    // double d1 = sqrt(pow(pPistao.getX() - pConectionVira.getX(), 2) + pow(pPistao.getY() - pConectionVira.getY(), 2) + pow(pPistao.getZ() - pConectionVira.getZ(), 2));
    // printf("distance: %.1f\n", d1);

    Object::transform();
}

void Biela::connect(Point ptConnection, double ang) {
    pConectionVira = ptConnection.copy();

    double xPistao = length * cos(ang);
    double yPistao = length * sin(ang);

    // na origem
    pPistao = Point(xPistao, yPistao, 0);
    pPistao.rotateY(angY);
    pPistao.rotateX(angX);
    // translada para ficar de acordo com o ponto do virabrequim
    pPistao.translate(pConectionVira);

    angZ = ang - PI / 2;
    transform();
}

int Biela::getLength() {
    return length;
}

Point Biela::getConnectionPistao() {
    return pPistao;
}

Point Biela::getConnectionPistaoTranf() {
    return pPistao.copy();
}
