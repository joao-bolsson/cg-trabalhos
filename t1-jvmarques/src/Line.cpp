/**
 * Implements a Line.
 *
 * @author João Bolsson (jvmarques@inf.ufsm.br)
 * @since 2018, 12 May.
 */
#include "Line.h"

Line::Line(Point p1, Point p2) {
    this->p1 = p1;
    this->p2 = p2;
    pivo = p1;
}

Point Line::getP1() {
    return p1;
}

Point Line::getP2() {
    return p2;
}

void Line::setP1(Point p1) {
    this->p1 = p1;
    pivo = p1;
}

void Line::setP2(Point p2) {
    this->p2 = p2;
}

void Line::render() {
    color(1, 0, 0);
    line(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void Line::translate(int x, int y) {
    // nao translada o pivo
    p2 = Point(p2.getX() + x, p2.getY() + y);
}

void Line::rotate(bool d) {
    int factor = -1;
    if (d) {
        factor = 1;
    }

    Point p = p2;

    double x = p.getX() * cos(ROTATE) - factor * p.getY() * sin(ROTATE);
    double y = factor * p.getX() * sin(ROTATE) + p.getY() * cos(ROTATE);

    p2 = Point(x, y);
}
