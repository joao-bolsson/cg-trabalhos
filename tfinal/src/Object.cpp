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
            p.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

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
