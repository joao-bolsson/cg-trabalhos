#include "Object.h"

Object::Object(Point center) {
    this->center = center;
}

void Object::setDistance(int d) {
    this->distance = d;
    transform();
}

void Object::rotate(double angX, double angY, double angZ) {
    this->angX = angX;
    this->angY = angY;
    this->angZ = angZ;
    transform();
}

Point Object::getTranslatePoint() {
    return translatePoint.copy();
}

Point Object::getCenter() {
    return center.copy();
}

Point Object::getCenterTransformed() {
    return centerTransformed.copy();
}

void Object::setShow2d(bool flag) {
    show2d = flag;
}

bool Object::isShow2d() {
    return show2d;
}

void Object::transform() {
    centerTransformed = center.copy();
    centerTransformed.translate(0, 0, 150);
    centerTransformed.project(distance);
    centerTransformed.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

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

double Object::getAngY() {
    return angY;
}

double Object::getAngX() {
    return angX;
}

double Object::getAngZ() {
    return angZ;
}
