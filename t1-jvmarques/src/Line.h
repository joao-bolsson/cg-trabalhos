/**
 * Defines a Line.
 *
 * @author João Bolsson (jvmarques@inf.ufsm.br)
 * @since 2018, 12 May.
 */

#ifndef __LINE_H
#define __LINE_H

#include "Point.h"
#include "gl_canvas2d.h"

const float ROTATE = 0.08;

class Line {

protected:
    Point p1, p2, pivo;

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

    void render();

    void translate(int x, int y);

    void rotate(bool d);
};

#endif
