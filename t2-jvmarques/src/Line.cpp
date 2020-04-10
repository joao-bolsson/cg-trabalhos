#include "Line.h"

Line::Line(Point p1, Point p2) {
    this->p1 = p1;
    this->p2 = p2;
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

Shape *Line::copy() {
    return new Line(p1, p2);
}
