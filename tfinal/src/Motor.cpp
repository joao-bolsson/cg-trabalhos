#include "Motor.h"

Motor::Motor(Point center) : Object(center) {
    // TODO
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
}

float Motor::calcAngPistao() {
    return 0;
}