#include "Cylinder.h"
#include "gl_canvas2d.h"
#include <math.h>

#define PI 3.14159265359

Cylinder::Cylinder(int r, int height, Point center) {
    float step = 0.35; // 20 graus

    float yBegin = center.getY() - height / 2;

    for (int h = 0; h <= height; h += 10) {
        vector<Point> line;
        for (float teta = 0; teta <= 2 * PI; teta += step) {
            float x = r * sin(teta);
            float y = yBegin + h;
            float z = r * cos(teta);

            Point p = Point(x, y, z);

            line.push_back(p);
        }
        ori.push_back(line);
    }

    transform();
}

void Cylinder::setDistance(int d) {
    this->distance = d;
    transform();
}

int Cylinder::getDistance() {
    return distance;
}

void Cylinder::setAngX(float ang) {
    this->angX = ang;
    transform();
}

float Cylinder::getAngX() {
    return angX;
}

void Cylinder::setAngY(float ang) {
    printf("angy: %.1f\n", ang);
    this->angY = ang;
    transform();
}

float Cylinder::getAngY() {
    return angY;
}

void Cylinder::setAngZ(float ang) {
    this->angZ = ang;
    transform();
}

float Cylinder::getAngZ() {
    return angZ;
}

void Cylinder::transform() {
    transformed.clear();

    for (auto line : ori) {
        vector<Point> transfLine; // transformed line
        for (auto point : line) {
            Point p = point.copy();
            p.transform(distance, angX, angY, 300, 300);

            transfLine.push_back(p);
        }
        transformed.push_back(transfLine);
    }
}

void Cylinder::render() {
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
}