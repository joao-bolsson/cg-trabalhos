#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Point.h"
#include <vector>

using namespace std;
class Object {
protected:
    float angX = 0, angY = 0, angZ = 0;
    Point translatePoint = Point(0, 0, 0);
    int distance = 70;
    Point center;

    vector<vector<Point>> points;
    vector<vector<Point>> transformed;

public:
    Object(Point center);

    virtual void render() = 0;
    void translate(Point p);
    void rotate(float angX, float angY, float angZ);
    void transform();

    void setDistance(int d);
    int getDistance();

    float getAngY();
    float getAngX();
    float getAngZ();
};

#endif
