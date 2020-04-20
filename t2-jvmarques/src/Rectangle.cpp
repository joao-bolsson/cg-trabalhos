#include "Rectangle.h"

using namespace std;

RectangleC::RectangleC(Point p1, Point p2) : Line(p1, p2) {
    short width = p1.getX() - p2.getX();
    short height = p1.getY() - p2.getY();

    p3 = Point(p1.getX() - width, p1.getY());
    p4 = Point(p1.getX(), p1.getY() - height);

    v3 = p3;
    v4 = p4;

    id = RECTANGLE;
}

void RectangleC::setP3(Point p3) {
    this->p3 = p3;
    v3 = p3;
    rotateCounter = 0;
}

void RectangleC::setP4(Point p4) {
    this->p4 = p4;
    v4 = p4;
    rotateCounter = 0;
}

Point RectangleC::getP3() {
    return p3;
}

Point RectangleC::getP4() {
    return p4;
}

void RectangleC::draw(Canvas *canvas) {
    canvas->color(1, 0, 0);

    canvas->line(p1.getX(), p1.getY(), p3.getX(), p3.getY());
    canvas->line(p1.getX(), p1.getY(), p4.getX(), p4.getY());
    canvas->line(p3.getX(), p3.getY(), p2.getX(), p2.getY());
    canvas->line(p4.getX(), p4.getY(), p2.getX(), p2.getY());
}

void RectangleC::drawSelectionBox(Canvas *canvas) {
    canvas->color(1, 0, 0);

    canvas->circleFill(p1.getX(), p1.getY(), r, div);
    canvas->circleFill(p2.getX(), p2.getY(), r, div);
    canvas->circleFill(p3.getX(), p3.getY(), r, div);
    canvas->circleFill(p4.getX(), p4.getY(), r, div);
}

void RectangleC::translate(int x, int y) {
    // nao translada o pivo
    p2 = Point(p2.getX() + x, p2.getY() + y);
    p3 = Point(p3.getX() + x, p3.getY() + y);
    p4 = Point(p4.getX() + x, p4.getY() + y);

    v2 = Point(v2.getX() + x, v2.getY() + y);
    v3 = Point(v3.getX() + x, v3.getY() + y);
    v4 = Point(v4.getX() + x, v4.getY() + y);
}

void RectangleC::rotate(bool d) {
    if (d) {
        rotateCounter--;
    } else {
        rotateCounter++;
    }

    unsigned int count = abs(rotateCounter);

    Point shapePoints[3] = {v2, v3, v4};

    int factor = -1;
    if (rotateCounter < 0) {
        factor = 1;
    }

    for (unsigned int i = 0; i < 3; i++) {
        Point p = shapePoints[i];

        double x = p.getX() * cos(ROTATE * count) - factor * p.getY() * sin(ROTATE * count);
        double y = factor * p.getX() * sin(ROTATE * count) + p.getY() * cos(ROTATE * count);

        shapePoints[i] = Point(x, y);
    }

    p2 = shapePoints[0];
    p3 = shapePoints[1];
    p4 = shapePoints[2];
}

Shape *RectangleC::copy() {
    RectangleC *rect = new RectangleC(p1, p2);
    rect->setP3(p3);
    rect->setP4(p4);

    return rect;
}
