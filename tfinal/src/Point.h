#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

class Point {
private:
    double x, y, z;

public:
    Point();
    Point(double x, double y, double z);

    Point copy();

    double getX();
    double getY();
    double getZ();

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    void translate(double x, double y, double z);
    void project(double d);
    void rotateX(double ang);
    void rotateY(double ang);
    void rotateZ(double ang);

    void print();
};

#endif
