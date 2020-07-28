#include "Pistao.h"

Pistao::Pistao(int radius, int length, Point center) : Cylinder(radius, length, center) {
    // empty
}

void Pistao::render() {
    if (1 > 2) {
        color(0, 1, 1);
        circle(pBiela.getX(), pBiela.getY(), 3, 10);
        return;
    }
    Cylinder::render();
}

void Pistao::transform() {
    // projeta o ponto de conexão com a biela
    Point p = pConectionBiela.copy();
    p.translate(0, 0, 150);
    p.project(distance);

    Point pViraTranslate = Point(translatePoint.getX() - p.getX(), translatePoint.getY() - p.getY(), translatePoint.getZ());

    p.translate(pViraTranslate);

    pBiela = p;

    Object::transform();
}

void Pistao::connect(Point ptConnection) {
    pConectionBiela = ptConnection.copy();
    transform();
}
