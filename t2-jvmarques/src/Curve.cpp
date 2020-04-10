#include "Curve.h"

Curve::Curve() {
    id = CURVE;
}

void Curve::addPoint(Point *p) {
    controlPoints.push_back(p);
    if (controlPoints.size() == 1) {
        pivo = Point(p->getX(), p->getY());
    }
}

vector<Point *> Curve::getControlPts() {
    return controlPoints;
}

void Curve::changePoint(int i, int x, int y) {
    Point *p = controlPoints[i];

    p->setX(x);
    p->setY(y);

    if (i == 0) {
        pivo = Point(x, y);
    }
}

void Curve::draw(Canvas *canvas) {
    canvas->color(1, 0, 0);

    unsigned int lastIndex = controlPoints.size() - 1;
    Point *first = controlPoints[0];
    Point *last = controlPoints[lastIndex];

    // desenha o primeiro e ultimo ponto de controle
    canvas->circleFill(first->getX(), first->getY(), r, div);
    canvas->circleFill(last->getX(), last->getY(), r, div);

    // desenha a curva
    for (float t = 0; t <= 1; t += 0.001) {
        double p1 = (pow(1 - t, 3) * controlPoints[0]->getX()) + (3 * t * pow(1 - t, 2) * controlPoints[1]->getX()) + (3 * pow(t, 2) * (1 - t) * controlPoints[2]->getX()) + (pow(t, 3) * controlPoints[3]->getX());
        double p2 = (pow(1 - t, 3) * controlPoints[0]->getY()) + (3 * t * pow(1 - t, 2) * controlPoints[1]->getY()) + (3 * pow(t, 2) * (1 - t) * controlPoints[2]->getY()) + (pow(t, 3) * controlPoints[3]->getY());
        canvas->point(p1, p2);
    }
}

void Curve::drawSelectionBox(Canvas *canvas) {
    // desenha os pontos de controle
    for (unsigned int i = 0; i < controlPoints.size(); i++) {
        Point *p = controlPoints[i];
        canvas->circleFill(p->getX(), p->getY(), 5, 10);
    }
}

bool Curve::isSelected(Point point) {
    int left = 20000, right = 0, top = 0, bottom = 2000000;

    // varre os pontos de controle para encontrar as extremidades
    for (unsigned int i = 0; i < controlPoints.size(); i++) {
        Point *p = controlPoints[i];

        int x = p->getX();
        int y = p->getY();

        if (x < left) {
            left = x;
        }

        if (x > right) {
            right = x;
        }

        if (y < bottom) {
            bottom = y;
        }

        if (y > top) {
            top = y;
        }
    }

    return (point.getX() >= left && point.getX() <= right && point.getY() >= bottom && point.getY() <= top);
}

void Curve::translate(int x, int y) {
    // nao translada o pivo
    for (unsigned int i = 1; i < controlPoints.size(); i++) {
        Point *p = controlPoints[i];

        changePoint(i, p->getX() + x, p->getY() + y);
    }
}

void Curve::rotate(bool d) {
    int factor = -1;
    if (d) {
        factor = 1;
    }

    for (unsigned int i = 1; i < controlPoints.size(); i++) {
        Point p = Point(controlPoints[i]->getX(), controlPoints[i]->getY());

        double x = p.getX() * cos(ROTATE) - factor * p.getY() * sin(ROTATE);
        double y = factor * p.getX() * sin(ROTATE) + p.getY() * cos(ROTATE);

        changePoint(i, x, y);
    }
}

Shape *Curve::copy() {
    Curve *curve = new Curve();

    // adiciona pontos de controle
    for (unsigned int i = 0; i < controlPoints.size(); i++) {
        Point *p = new Point(controlPoints[i]->getX(), controlPoints[i]->getY());

        curve->addPoint(p);
    }
    return curve;
}

int Curve::isSelectedPointCtrl(Point point) {
    for (unsigned int i = 0; i < controlPoints.size(); i++) {
        Point *p = controlPoints[i];

        int x1 = p->getX() - r;
        int y1 = p->getY() + r;

        int x2 = p->getX() + r;
        int y2 = p->getY() - r;

        int x = point.getX();
        int y = point.getY();

        if (x >= x1 && x <= x2 && y >= y2 && y <= y1) {
            return i;
        }
    }
    return -1;
}
