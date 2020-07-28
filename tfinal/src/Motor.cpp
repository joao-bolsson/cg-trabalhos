#include "Motor.h"

Motor::Motor(Point center) : Object(center) {
    virabrequim = new Virabrequim(10, 40, center);
    biela = new Biela(5, 80, center);
    pistao = new Pistao(10, 20, center);
}

void Motor::translate(Point p) {
    virabrequim->translate(p);

    Point t = virabrequim->getPtConnectionTransf();
    t.translate(0, 0, 150);
    t.project(distance);
    t.translate(p.getX(), p.getY(), p.getZ());
    biela->translate(p);

    pistao->translate(p);

    Object::translate(p);
}

void Motor::rotate(double angX, double angY, double angZ) {
    virabrequim->rotate(angX, angY, angZ);

    // apenas o ponto de conexão da biela com o virabrequim tem que rotacionar no eixo z
    // TODO: biela tem que rotacionar no eixo z o valor do angulo entre o pVirabrequim e o ptPistao
    biela->rotate(angX, angY, 0);
    pistao->rotate(angX, angY, 0);

    Object::rotate(angX, angY, angZ);
}

void Motor::render() {
    virabrequim->render();
    biela->render();
    pistao->render();
}

void Motor::transform() {
    double ang = calcAngPistao();
    Point translBiela = virabrequim->getPtConnectionTransf();
    translBiela.translate(0, 0, 150);
    translBiela.project(distance);
    translBiela.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());
    biela->translate(translBiela);

    biela->connect(virabrequim->getPtConnectionTransf(), ang);

    Point pConectionVira = virabrequim->getPtConnectionTransf();
    Point translPistao = biela->getConnectionPistaoTranf();
    translPistao.translate(-pConectionVira.getX(), -pConectionVira.getY(), -pConectionVira.getZ());
    translPistao.translate(0, 0, 150);
    translPistao.project(distance);
    translPistao.translate(translBiela.getX(), translBiela.getY(), translBiela.getZ());
    pistao->translate(translPistao);

    pistao->connect(biela->getConnectionPistaoTranf());

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
    Point ptVirabrequim = virabrequim->getPtConnection().copy();
    ptVirabrequim.translate(-virabrequim->getCenter().getX(), -virabrequim->getCenter().getY(), -virabrequim->getCenter().getZ());
    ptVirabrequim.rotateZ(angZ);
    ptVirabrequim.translate(-virabrequim->getCenter().getX(), -virabrequim->getCenter().getY(), -virabrequim->getCenter().getZ());

    float length = biela->getLength();
    double xVirabrequim = ptVirabrequim.getX();
    double yVirabrequim = ptVirabrequim.getY();
    double cateto = sqrt(length * length - xVirabrequim * xVirabrequim);

    double xPistao = virabrequim->getCenter().getX();
    double yPistao = cateto + yVirabrequim;

    Point ptPistao = Point(xPistao, yPistao, virabrequim->getCenter().getZ());
    Point ptCenter = Point(ptPistao.getX(), ptVirabrequim.getY(), virabrequim->getCenter().getX());

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

    // rotaciona aqui apenas para mostrar os vetores na canvas
    // ptVirabrequim.translate(-virabrequim->getCenter().getX(), -virabrequim->getCenter().getY(), -virabrequim->getCenter().getZ());
    // ptVirabrequim.rotateY(angY);
    // ptVirabrequim.rotateX(angX);
    // ptVirabrequim.translate(-virabrequim->getCenter().getX(), -virabrequim->getCenter().getY(), -virabrequim->getCenter().getZ());
    // // termina rotacao

    // ptVirabrequim.translate(0, 0, 150);
    // ptVirabrequim.project(distance);

    // ptPistao.translate(0, 0, 150);
    // ptPistao.project(distance);

    // ptCenter.translate(0, 0, 150);
    // ptCenter.project(distance);

    // ptVirabrequim.translate(translatePoint.getX(), translatePoint.getY(), 0);
    // ptPistao.translate(ptVirabrequim.getX(), ptVirabrequim.getY(), 0);
    // ptCenter.translate(ptVirabrequim.getX(), ptVirabrequim.getY(), 0);

    // color(1, 0, 0);
    // line(ptVirabrequim.getX(), ptVirabrequim.getY(), ptCenter.getX(), ptCenter.getY());
    // color(0, 0, 1);
    // line(ptVirabrequim.getX(), ptVirabrequim.getY(), ptPistao.getX(), ptPistao.getY());

    // color(1, 0, 0);
    // circle(ptVirabrequim.getX(), ptVirabrequim.getY(), 3, 10);

    // color(0, 1, 0);
    // circle(ptPistao.getX(), ptPistao.getY(), 3, 10);

    // color(0, 0, 1);
    // circle(ptCenter.getX(), ptCenter.getY(), 3, 10);

    // if (1 > 0) {
    //     return PI / 2;
    // }

    return acos(calc);
}