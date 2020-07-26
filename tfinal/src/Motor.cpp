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
    biela->rotate(angX, angY, angZ);
    // biela->rotateObject(angX, angY, calcAngPistao());

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

    // TODO: não pode mais pq esse ponto nao esta projetado
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
    Point ptVirabrequim = virabrequim->getPtConnectionTransf();
    // acabou o calc do ponto p (virabrequim)

    Point centerVira = virabrequim->getCenter();

    float cateto = sqrt(pow(biela->getLength(), 2) - pow(ptVirabrequim.getX(), 2));

    // onde a biela se conecta com o pistao
    Point ptPistao = Point(centerVira.getX(), ptVirabrequim.getY() + cateto, centerVira.getZ());
    // acabou o calc do ponto b (pistao)

    // acha o angulo
    double tgAlfa = (ptPistao.getY() - ptVirabrequim.getY()) / (ptPistao.getX() - ptVirabrequim.getX());
    tgAlfa = tan(tgAlfa);

    // faz as transformações pra desenhar na tela (teste)
    // ptVirabrequim.translate(0, 0, 150);

    // ptVirabrequim.project(distance);

    // // return back to the original center
    // ptVirabrequim.translate(center.getX(), center.getY(), center.getZ());

    // // optional: centralizing in another point on screen
    // ptVirabrequim.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    // ptPistao.translate(0, 0, 150);

    // ptPistao.project(distance);

    // // return back to the original center
    // ptPistao.translate(center.getX(), center.getY(), center.getZ());

    // // optional: centralizing in another point on screen
    // ptPistao.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    // line(ptVirabrequim.getX(), ptVirabrequim.getY(), ptPistao.getX(), ptPistao.getY());
    // color(1, 0, 0);
    // circle(ptPistao.getX(), ptPistao.getY(), 5, 10);

    return atan(tgAlfa);
}