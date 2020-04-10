#ifndef __SHAPE_H
#define __SHAPE_H

#include "Canvas.h"
#include "Point.h"
#include <vector>

const char SHAPE = 0;
const char LINE = 1;
const char RECTANGLE = 2;
const char CURVE = 3;
const float ROTATE = 0.08;

class Shape {

protected:
    char r = 5, div = 10, id;
    Point pivo;

public:
    /**
     * Default construct
     */
    Shape();

    /**
     * @return The shape identifier.
     */
    char getId();

    /**
     * Draw the shape.
     * @param canvas Referenced canvas to draw.
     */
    virtual void draw(Canvas *canvas);

    /**
     * Draw the selection box of the shape.
     * @param canvas Referenced canvas.
     */
    virtual void drawSelectionBox(Canvas *canvas);

    /**
     * @param x Clicked point.
     * @return If the point is inside of the selection box - true, else - false.
     */
    virtual bool isSelected(Point x);

    /**
     * Translate the shape.
     * @param x Translate on axis x.
     * @param y Translate on axis y.
     */
    virtual void translate(int x, int y);

    /**
     * @return Return the pivo.
     */
    Point getPivo();

    /**
     * Rotate the shape.
     * @param d If true - rotate to the left, false - right.
     */
    virtual void rotate(bool d);

    /**
     * @return A copy of this shape.
     */
    virtual Shape *copy();
};

#endif
