#include "Cylinder.h"
#include "gl_canvas2d.h"
#include <math.h>

#define PI 3.14159265359

Cylinder::Cylinder(int r, Point center) {
    float step = 0.35; // 20 graus

    vector<Point> line;
    vector<Point> lineTransf;
    for (float teta = 0; teta <= 2 * PI; teta += step) {
        float x, y, z;
        x = r * sin(teta);
        y = center.getY();
        z = r * cos(teta);

        Point p = Point(x, y, z);

        line.push_back(p);
        lineTransf.push_back(p.copy());
    }

    ori.push_back(line);
    transformed.push_back(lineTransf);
}

void Cylinder::setAngX(float ang) {
    this->angX = ang;
    transform();
}

float Cylinder::getAngX() {
    return angX;
}

void Cylinder::setAngY(float ang) {
    this->angY = ang;
    transform();
}

float Cylinder::getAngY() {
    return angY;
}

void Cylinder::transform() {
    for (unsigned int l = 0; l < ori.size(); l++) {
        vector<Point> lines = ori[l];

        vector<Point> other;
        for (unsigned int c = 0; c < lines.size(); c++) {
            Point p = lines[c].copy();

            p.transform(distance, angX, angY, 300, 300);

            other.push_back(p);
        }

        transformed[l] = other;
    }

    vector<Point> transf = transformed[0];
}

void Cylinder::render() {
    color(1, 0, 0);

    for (unsigned int l = 0; l < transformed.size(); l++) {
        vector<Point> lines = transformed[l];
        for (unsigned int c = 0; c < lines.size() - 1; c++) {
            Point p1 = lines[c];
            Point p2 = lines[c + 1];

            line(p1.getX(), p1.getY(), p2.getX(), p2.getY());
        }
        // connect the last with the first
        Point first = lines[0];
        Point last = lines[lines.size() - 1];
        line(first.getX(), first.getY(), last.getX(), last.getY());
    }
}