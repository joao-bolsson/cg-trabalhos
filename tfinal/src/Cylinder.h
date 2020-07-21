#ifndef CYLINDER_H_INCLUDED
#define CYLINDER_H_INCLUDED

#include "Point.h"
#include <vector>

using namespace std;
class Cylinder {
private:
    vector<vector<Point>> ori;
    vector<vector<Point>> transformed;

    float angX = 0;
    float angY = 0;
    float angZ = 0;

    int distance = 70;

public:
    Cylinder(int r, int height, Point center);

    void render();
    void transform();

    void setDistance(int d);
    int getDistance();

    void setAngY(float ang);
    float getAngY();

    void setAngX(float ang);
    float getAngX();

    void setAngZ(float ang);
    float getAngZ();
};

#endif
