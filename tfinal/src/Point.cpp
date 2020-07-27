#include "Point.h"
#include <math.h>

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point Point::copy() {
    return Point(x, y, z);
}

double Point::getX() {
    return x;
}

double Point::getY() {
    return y;
}

double Point::getZ() {
    return z;
}

void Point::setX(double x) {
    this->x = x;
}

void Point::setY(double y) {
    this->y = y;
}

void Point::setZ(double z) {
    this->z = z;
}

void Point::translate(double x, double y, double z) {
    this->x += x;
    this->y += y;
    this->z += z;
}

void Point::translate(Point p) {
    translate(p.getX(), p.getY(), p.getZ());
}

void Point::rotateX(double ang) {
    double yTemp = cos(ang) * this->y - sin(ang) * this->z;
    double zTemp = sin(ang) * this->y + cos(ang) * this->z;

    this->y = yTemp;
    this->z = zTemp;
}

void Point::rotateY(double ang) {
    double xTemp = cos(ang) * this->x + sin(ang) * this->z;
    double yTemp = cos(ang) * this->z - sin(ang) * this->x;

    this->x = xTemp;
    this->z = yTemp;
}

void Point::rotateZ(double ang) {
    double xTemp = cos(ang) * this->x - sin(ang) * this->y;
    double yTemp = sin(ang) * this->x + cos(ang) * this->y;

    this->x = xTemp;
    this->y = yTemp;
}

void Point::project(double d) {
    this->x = this->x * d / this->z;
    this->y = this->y * d / this->z;
    this->z = 0;
}

void Point::print() {
    printf("p(%.1f, %.1f, %.1f)\n", x, y, z);
}
