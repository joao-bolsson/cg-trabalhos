#include "Point.h"
#include <math.h>

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point Point::copy() {
    return Point(x, y, z);
}

float Point::getX() {
    return x;
}

float Point::getY() {
    return y;
}

float Point::getZ() {
    return z;
}

void Point::setX(float x) {
    this->x = x;
}

void Point::setY(float y) {
    this->y = y;
}

void Point::setZ(float z) {
    this->z = z;
}

void Point::translate(float x, float y, float z) {
    this->x += x;
    this->y += y;
    this->z += z;
}

void Point::rotateX(float ang) {
    float yTemp = cos(ang) * this->y - sin(ang) * this->z;
    float zTemp = sin(ang) * this->y + cos(ang) * this->z;

    this->y = yTemp;
    this->z = zTemp;
}

void Point::rotateY(float ang) {
    float xTemp = cos(ang) * this->x + sin(ang) * this->z;
    float yTemp = cos(ang) * this->z - sin(ang) * this->x;

    this->x = xTemp;
    this->z = yTemp;
}

void Point::rotateZ(float ang) {
    float xTemp = cos(ang) * this->x - sin(ang) * this->y;
    float yTemp = sin(ang) * this->x + cos(ang) * this->y;

    this->x = xTemp;
    this->y = yTemp;
}

void Point::project(float d) {
    this->x = this->x * d / this->z;
    this->y = this->y * d / this->z;
    this->z = 0;
}
