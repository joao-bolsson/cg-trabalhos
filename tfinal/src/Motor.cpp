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
    // TODO: biela tem que rotacionar no eixo z o valor do angulo entre o pVirabrequim e o pPistao
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
    // double ang = calcAngPistao();
    biela->connect(virabrequim->getPtConnection(), 0);
    pistao->connect(biela->getConnectionPistao());

    // biela->translate(virabrequim->getPtConnectionTransf());

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
    Point origem = biela->getConnectionPistaoTranf().copy(); //virabrequim->getPtConnection();
    Point v = virabrequim->getPtConnectionTransf();
    Point u = translatePoint.copy();

    v.translate(-origem.getX(), -origem.getY(), -origem.getZ());
    u.translate(-origem.getX(), -origem.getY(), -origem.getZ());

    double x1 = u.getX();
    double y1 = u.getY();
    double x2 = v.getX();
    double y2 = v.getY();

    double val = (x1 * x2 + y1 * y2) / (sqrt(pow(x1, 2) + pow(y1, 2)) * sqrt(pow(x2, 2) + pow(y2, 2)));
    double cosv = cos(val);
    double ang = acos(cosv);
    printf("ang: %.2f\n", ang);

    // if (virabrequim->getPtConnectionTransf().getX() < translatePoint.getX()) {
    //     return -ang;
    // }

    return 0;
}