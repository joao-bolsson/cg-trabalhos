#include "Biela.h"

Biela::Biela(Point center) : Object(center) {
}

void Biela::render() {
    color(0, 0, 1);
    int height = 80;
    line(pVirabrequim.getX(), pVirabrequim.getY(), pVirabrequim.getX(), pVirabrequim.getY() + height);
}

void Biela::transform() {
    // TODO
}

void Biela::connect(Point ptConnection, float ang) {
    pVirabrequim = ptConnection;
}