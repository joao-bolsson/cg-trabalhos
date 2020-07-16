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
    // TODO: nao usar o valor de y modificado, criar variavel temp
    this->y = cos(ang) * this->y - sin(ang) * this->z;
    this->z = sin(ang) * this->y + cos(ang) * this->z;
}

void Point::rotateY(float ang) {
    this->x = cos(ang) * this->x + sin(ang) * this->z;
    this->z = cos(ang) * this->z - sin(ang) * this->x;
}

void Point::rotateZ(float ang) {
    this->x = cos(ang) * this->x - sin(ang) * this->y;
    this->y = sin(ang) * this->x + cos(ang) * this->y;
}

void Point::project(float d) {
    this->x = this->x * d / this->z;
    this->y = this->y * d / this->z;
    this->z = 0;
}

void Point::transform(int d, float angX, float angY, int translateX, int translateY) {
    rotateY(angY);
    rotateX(angX);

    this->z += 150;

    project(d);

    translate(translateX, translateY, 0);
}
