#include "Pistao.h"

Pistao::Pistao(int radius, int length, Point center) : Object(center) {
    this->length = length;

    double step = 0.35; // 20 graus

    double height = length;

    double yBegin = center.getY();

    for (int h = 0; h <= height; h += 10) {
        vector<Point> line;
        for (double teta = 0; teta <= 2 * PI; teta += step) {
            double x = radius * sin(teta);
            double y = yBegin + h;
            double z = radius * cos(teta);

            Point p = Point(x, y, z);

            line.push_back(p);
        }
        points.push_back(line);
    }
}

void Pistao::render() {
    color(0, 1, 1);
    if (1 > 2) {
        circle(pBiela.getX(), pBiela.getY(), 3, 10);
        return;
    }
    ///////////// mesmo codigo de cylinder::render
    for (unsigned int l = 0; l < transformed.size(); l++) {
        color(1, 0, 0);
        vector<Point> points = transformed[l];
        double r = 0.1, g = 0.2, b = 0.3;
        for (unsigned int c = 0; c < points.size() - 1; c++) {
            Point p1 = points[c];
            Point p2 = points[c + 1];

            line(p1.getX(), p1.getY(), p2.getX(), p2.getY());

            if (l < transformed.size() - 1) {
                color(r, g, b);
                p2 = transformed[l + 1][c];
                line(p1.getX(), p1.getY(), p2.getX(), p2.getY());

                p2 = transformed[l + 1][c + 1];
                line(p1.getX(), p1.getY(), p2.getX(), p2.getY());
            }
            r += 0.02;
            g += 0.01;
            b += 0.02;
        }
        // connect the last with the first
        Point first = points[0];
        Point last = points[points.size() - 1];
        line(first.getX(), first.getY(), last.getX(), last.getY());

        if (l < transformed.size() - 1) {
            last = transformed[l + 1][0];
            line(first.getX(), first.getY(), last.getX(), last.getY());

            int size = transformed[l + 1].size();
            last = transformed[l + 1][size - 1];
            line(first.getX(), first.getY(), last.getX(), last.getY());
        }
    }
    //////////////////
}

void Pistao::transform() {
    // projeta o ponto de conexão com a biela
    Point p = pConectionBiela.copy();
    p.translate(0, 0, 150);
    p.project(distance);

    Point pViraTranslate = Point(translatePoint.getX() - p.getX(), translatePoint.getY() - p.getY(), translatePoint.getZ());

    p.translate(pViraTranslate);

    pBiela = p;

    Object::transform();
}

void Pistao::connect(Point ptConnection) {
    pConectionBiela = ptConnection.copy();
    transform();
}
