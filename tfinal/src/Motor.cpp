#include "Motor.h"

Motor::Motor(Point center) : Object(center) {
    virabrequim = new Virabrequim(10, 70, center);
    biela = new Biela(80, center);
    pistao = new Pistao(center);
}

void Motor::translate(Point p) {
    virabrequim->translate(p);
    biela->translate(p);
    pistao->translate(p);

    Object::translate(p);
}

void Motor::rotate(float angX, float angY, float angZ) {
    virabrequim->rotate(angX, angY, angZ);
    biela->rotate(angX, angY, angZ);
    pistao->rotate(angX, angY, angZ);

    Object::rotate(angX, angY, angZ);
}

void Motor::render() {
    virabrequim->render();
    biela->render();
    pistao->render();
}

void Motor::transform() {
    float ang = calcAngPistao();
    biela->connect(virabrequim->getPtConnection(), ang);
    pistao->connect(biela->getConnectionPistao());

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

float Motor::calcAngPistao() {
    return 0;
}