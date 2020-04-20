#include "Line.h"

Line::Line(Point p1, Point p2) {
    this->p1 = p1;
    this->p2 = p2;

    this->v2 = p2;

    pivo = p1;
    id = LINE;
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
    this->v2 = p2;
    rotateCounter = 0;
}

void Line::draw(Canvas *canvas) {
    canvas->color(1, 0, 0);
    canvas->line(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void Line::drawSelectionBox(Canvas *canvas) {
    canvas->color(1, 0, 0);
    short width = p1.getX() - p2.getX();
    short height = p1.getY() - p2.getY();

    canvas->circleFill(p1.getX(), p1.getY(), r, div);
    canvas->circleFill(p2.getX(), p2.getY(), r, div);
    canvas->circleFill(p1.getX() - width, p1.getY(), r, div);
    canvas->circleFill(p1.getX(), p1.getY() - height, r, div);
}

bool Line::isSelected(Point x) {
    if ((p1.getX() >= x.getX() && p2.getX() <= x.getX()) || (p1.getX() <= x.getX() && p2.getX() >= x.getX())) {

        // compara os y
        if ((p1.getY() >= x.getY() && p2.getY() <= x.getY()) || (p1.getY() <= x.getY() && p2.getY() >= x.getY())) {
            return true;
        }
    }
    return false;
}

void Line::translate(int x, int y) {
    // nao translada o pivo
    p2 = Point(p2.getX() + x, p2.getY() + y);
    v2 = Point(v2.getX() + x, v2.getY() + y);
}

void Line::rotate(bool d) {
    if (d) {
        rotateCounter--;
    } else {
        rotateCounter++;
    }

    unsigned int count = abs(rotateCounter);
    Point p = v2;

    int factor = -1;
    if (rotateCounter < 0) {
        factor = 1;
    }

    double x = p.getX() * cos(ROTATE * count) - factor * p.getY() * sin(ROTATE * count);
    double y = factor * p.getX() * sin(ROTATE * count) + p.getY() * cos(ROTATE * count);

    p2 = Point(x, y);
}

Shape *Line::copy() {
    return new Line(p1, p2);
}
