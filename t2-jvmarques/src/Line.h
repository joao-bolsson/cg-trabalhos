#ifndef __LINE_H
#define __LINE_H

#include "Shape.h"

class Line : public Shape {

protected:
    Point p1, p2;

    /**
     * Stores the original value for the point 2.
     */
    Point v2;

    /**
     * Value greater than zero means rotate to right, and lower means rotate to left.
     */
    int rotateCounter = 0;

public:
    /**
     * Default construct.
     *
     * @param p1 Start point of line.
     * @param p2 End point of line.
     */
    Line(Point p1, Point p2);

    /**
     * Sets the start point.
     * @param p1 Point to set.
     */
    void setP1(Point p1);

    /**
     * Sets the end point.
     * @param p2 Point to set.
     */
    void setP2(Point p2);

    /**
     * @return The start point of line.
     */
    Point getP1();

    /**
     * @return The end point of line.
     */
    Point getP2();

    void draw(Canvas *canvas);

    void drawSelectionBox(Canvas *canvas);

    bool isSelected(Point x);

    void translate(int x, int y);

    void rotate(bool d);

    Shape *copy();
};

#endif
