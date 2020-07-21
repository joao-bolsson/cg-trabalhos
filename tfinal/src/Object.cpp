#include "Object.h"

Object::Object(Point center) {
    this->center = center;
}

void Object::setDistance(int d) {
    this->distance = d;
    transform();
}

void Object::rotate(float angX, float angY, float angZ) {
    this->angX = angX;
    this->angY = angY;
    this->angZ = angZ;
    transform();
}

void Object::transform() {
    transformed.clear();

    for (auto line : points) {
        vector<Point> transfLine; // transformed line
        for (auto point : line) {
            Point p = point.copy();
            p.transform(distance, angX, angY, translatePoint.getX(), translatePoint.getY());

            transfLine.push_back(p);
        }
        transformed.push_back(transfLine);
    }
}

void Object::translate(Point p) {
    this->translatePoint = p.copy();
    transform();
}

int Object::getDistance() {
    return distance;
}

float Object::getAngY() {
    return angY;
}

float Object::getAngX() {
    return angX;
}

float Object::getAngZ() {
    return angZ;
}
