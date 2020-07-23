#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class Point {
private:
    float x, y, z;

public:
    Point();
    Point(float x, float y, float z);

    Point copy();

    float getX();
    float getY();
    float getZ();

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void translate(float x, float y, float z);
    void project(float d);
    void rotateX(float ang);
    void rotateY(float ang);
    void rotateZ(float ang);
};

#endif
