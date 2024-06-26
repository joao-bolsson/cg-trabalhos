#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#define PI 3.14159265359

#include "Point.h"
#include "gl_canvas2d.h"
#include <vector>
#include <math.h>

using namespace std;
class Object {
protected:
    double angX = 0, angY = 0, angZ = 0;
    Point translatePoint = Point(0, 0, 0);
    int distance = 70;
    Point center;
    Point centerTransformed;

    vector<vector<Point>> points;
    vector<vector<Point>> transformed;

    bool show2d = false;

public:
    Object(Point center);

    virtual void render() = 0;
    virtual void translate(Point p);
    virtual void rotate(double angX, double angY, double angZ);
    virtual void transform();

    virtual void setDistance(int d);
    int getDistance();

    Point getCenter();
    Point getCenterTransformed();

    Point getTranslatePoint();

    double getAngY();
    double getAngX();
    double getAngZ();

    /**
     * Sets a flag to show or not the object in 2D.  
     * @param  flag: Flag to set.
     */
    virtual void setShow2d(bool flag);

    bool isShow2d();
};

#endif
