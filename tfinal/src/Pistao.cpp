#include "Pistao.h"

Pistao::Pistao(int radius, int length, int viraLength, Point center) : Cylinder(radius, length, center) {
    camisa = new Cylinder(radius, length + viraLength * 2, center);
}

void Pistao::render() {
    if (show2d) {
        color(0, 1, 1);
        circle(pBiela.getX(), pBiela.getY(), 3, 10);
        return;
    }
    Cylinder::render();
}

void Pistao::renderCamisa() {
    if (!show2d) {
        camisa->render();
    }
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

void Pistao::rotate(double angX, double angY, double angZ) {
    camisa->rotate(angX, angY, angZ);
    Object::rotate(angX, angY, angZ);
}

void Pistao::setDistance(int d) {
    camisa->setDistance(d);
    Object::setDistance(d);
}

void Pistao::connect(Point ptConnection) {
    pConectionBiela = ptConnection.copy();
    transform();
}

void Pistao::connectCamisa(Point p) {
    camisa->translate(p);
}
