#include "Motor.h"

Motor::Motor(Point center, int viraLength, int pistaoLength, int pistaoRadius) : Object(center) {
    virabrequim = new Virabrequim(10, viraLength, center);
    biela = new Biela(pistaoRadius / 2, viraLength * 2, center);
    pistao = new Pistao(pistaoRadius, pistaoLength, viraLength, center);
}

void Motor::translate(Point p) {
    virabrequim->translate(p);

    pistao->translate(p);

    Object::translate(p);
}

void Motor::setShow2d(bool flag) {
    Object::setShow2d(flag);

    virabrequim->setShow2d(flag);
    biela->setShow2d(flag);
    pistao->setShow2d(flag);
}

void Motor::rotate(double angX, double angY, double angZ) {
    virabrequim->rotate(angX, angY, angZ);
    biela->rotate(angX, angY, 0);
    pistao->rotate(angX, angY, 0);

    Object::rotate(angX, angY, angZ);
}

void Motor::render() {
    if (showVira) {
        virabrequim->render();
    }
    if (showBiela) {
        biela->render();
    }
    if (showPistao) {
        pistao->render();
    }
    if (showCamisa) {
        pistao->renderCamisa();
    }
}

void Motor::transform() {
    double ang = calcAngPistao();
    /**
     * A biela deve ser sempre transladada para ficar conectada com o virabrequim.
     * Pega o ponto de conexão virabrequim->biela (rotacionado em relação a origem) e projeta esse ponto.
     */
    Point translBiela = virabrequim->getPtConnectionTransf();
    translBiela.translate(0, 0, 150);
    translBiela.project(distance);
    translBiela.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());
    biela->translate(translBiela);

    biela->connect(virabrequim->getPtConnectionTransf(), ang);

    /**
     * Mesmo racionício da biela com o virabrequim, agora o pistão deve ser mostrado sempre em relação onde a biela está.
     */
    Point pConectionVira = virabrequim->getPtConnectionTransf();
    Point translPistao = biela->getConnectionPistaoTranf(); // já está rotacionado e transladado com pConectionVira
    translPistao.translate(-pConectionVira.getX(), -pConectionVira.getY(), -pConectionVira.getZ());
    translPistao.translate(0, 0, 150);
    translPistao.project(distance);
    translPistao.translate(translBiela.getX(), translBiela.getY(), translBiela.getZ());
    pistao->translate(translPistao);

    pistao->connect(biela->getConnectionPistaoTranf());

    // calcula o ponto onde a camisa vai ficar na tela
    Point viraCenter = virabrequim->getCenter();

    double yCamisa = viraCenter.getY() + (biela->getLength() - virabrequim->getLength());
    Point pTranslCamisa = Point(viraCenter.getX(), yCamisa, viraCenter.getZ());
    pTranslCamisa.rotateY(angY);
    pTranslCamisa.rotateX(angX);
    pTranslCamisa.translate(0, 0, 150);
    pTranslCamisa.project(distance);

    Point aux = virabrequim->getCenterTransformed();
    aux.setX(translPistao.getX());

    pTranslCamisa.translate(aux);

    pistao->connectCamisa(pTranslCamisa);

    virabrequim->transform();
    biela->transform();
    pistao->transform();

    Object::transform();
}

void Motor::setShowVira(bool flag) {
    showVira = flag;
}

void Motor::setShowBiela(bool flag) {
    showBiela = flag;
}

void Motor::setShowPistao(bool flag) {
    showPistao = flag;
}

void Motor::setShowCamisa(bool flag) {
    showCamisa = flag;
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