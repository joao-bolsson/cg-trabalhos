#ifndef CYLINDER_H_INCLUDED
#define CYLINDER_H_INCLUDED

#include "Point.h"
#include <vector>

#define LINES 1
#define COLUMNS 18

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
    Cylinder(int r, Point center);

    void render();
    void transform();

    void setAngY(float ang);
    float getAngY();

    void setAngX(float ang);
    float getAngX();
};

#endif
