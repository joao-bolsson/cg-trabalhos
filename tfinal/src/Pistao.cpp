#include "Pistao.h"

Pistao::Pistao(Point center, Point ptVira, Point ptViraCenter, int radius, int length, float bielaLength) : Object(center) {
    this->bielaLength = bielaLength;
    this->ptVira = ptVira;
    this->ptViraCenter = ptViraCenter;

    float cateto = sqrt(abs(bielaLength * bielaLength - ptVira.getX() * ptVira.getX()));
    float xPistao = ptViraCenter.getX(); // centro do virabrequim + tranlação
    float yPistao = cateto + ptVira.getY();

    ptConnection = Point(xPistao, yPistao, ptViraCenter.getZ());

    // controi o cilindro
    float step = 0.35; // 20 graus

    float height = length;

    float yBegin = ptConnection.getY();

    for (int h = 0; h <= height; h += 10) {
        vector<Point> line;
        for (float teta = 0; teta <= 2 * PI; teta += step) {
            float x = radius * sin(teta);
            float y = yBegin + h;
            float z = radius * cos(teta);

            Point p = Point(x, y, z);

            line.push_back(p);
        }
        points.push_back(line);
    }

    transform();
}

void Pistao::render() {
    color(1, 0, 0);
    circle(ptConnection.getX() + translatePoint.getX(), ptConnection.getY() + translatePoint.getY(), 3, 10);

    if (1 > 0) {
        return;
    }
    ///////////// mesmo codigo de cylinder::render
    for (unsigned int l = 0; l < transformed.size(); l++) {
        color(1, 0, 0);
        vector<Point> points = transformed[l];
        float r = 0.1, g = 0.2, b = 0.3;
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
    float cateto = sqrt(abs(bielaLength * bielaLength - ptVira.getX() * ptVira.getX()));
    float xPistao = ptViraCenter.getX(); // centro do virabrequim + tranlação
    float yPistao = cateto + ptVira.getY();

    ptConnection = Point(xPistao, yPistao, ptViraCenter.getZ());

    Point p = ptConnection.copy();

    // move to origin
    p.translate(-center.getX(), -center.getY(), -center.getZ());

    p.rotateZ(angZ);
    p.rotateY(angY);
    p.rotateX(angX);

    p.translate(0, 0, 150);

    p.project(distance);

    // return back to the original center
    p.translate(center.getX(), center.getY(), center.getZ());

    // optional: centralizing in another point on screen
    // p.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    ptConTransformed = p;
    // Object::transform();
}
