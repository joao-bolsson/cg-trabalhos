#include "Motor.h"

Motor::Motor(Point center) : Object(center) {
    virabrequim = new Virabrequim(10, 40, center);
    biela = new Biela(5, 80, center);
    pistao = new Pistao(center);
}

void Motor::translate(Point p) {
    virabrequim->translate(p);
    biela->translate(p);
    pistao->translate(p);

    Object::translate(p);
}

void Motor::rotate(double angX, double angY, double angZ) {
    virabrequim->rotate(angX, angY, angZ);

    // apenas o ponto de conexão da biela com o virabrequim tem que rotacionar no eixo z
    // TODO: biela tem que rotacionar no eixo z o valor do angulo entre o pVirabrequim e o ptPistao
    biela->rotate(angX, angY, 0);
    pistao->rotate(angX, angY, angZ);

    Object::rotate(angX, angY, angZ);
}

void Motor::render() {
    virabrequim->render();
    biela->render();
    pistao->render();
}

void Motor::transform() {
    double ang = calcAngPistao();
    biela->connect(virabrequim->getPtConnectionTransf(), ang);
    pistao->connect(biela->getConnectionPistao());

    // Point t = virabrequim->getPtConnectionTransf();
    // t.translate(0, 0, 150);
    // t.project(distance);
    // t.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());
    // biela->translate(t);

    virabrequim->transform();
    biela->transform();
    pistao->transform();

    Object::transform();
}

void Motor::setDistance(int d) {
    virabrequim->setDistance(d);
    biela->setDistance(d);
    pistao->setDistance(d);

    Object::setDistance(d);
}

double Motor::calcAngPistao() {
    Point ptVirabrequim = virabrequim->getPtConnectionTransf();

    float length = biela->getLength();
    double xVirabrequim = ptVirabrequim.getX();
    double yVirabrequim = ptVirabrequim.getY();
    double cateto = sqrt(length * length - xVirabrequim * xVirabrequim);

    double xPistao = virabrequim->getCenter().getX();
    double yPistao = cateto + yVirabrequim;

    Point ptPistao = Point(xPistao, yPistao, 0);
    Point ptCenter = Point(ptPistao.getX(), ptVirabrequim.getY(), 0);

    // translado para a origem
    ptPistao.translate(-ptVirabrequim.getX(), -ptVirabrequim.getY(), 0);
    ptCenter.translate(-ptVirabrequim.getX(), -ptVirabrequim.getY(), 0);

    // o vetor centro aponta para a direção oposta quando estiver à esquerda do virabrequim
    if (ptCenter.getX() < ptVirabrequim.getX()) {
        ptCenter.setX(-ptCenter.getX());
    }

    double x1 = ptPistao.getX();
    double y1 = ptPistao.getY();
    double x2 = ptCenter.getX();
    double y2 = ptCenter.getY();

    double calc = (x1 * x2 + y1 * y2) / (sqrt(pow(x1, 2) + pow(y1, 2)) * sqrt(pow(x2, 2) + pow(y2, 2)));
    return acos(calc);
}