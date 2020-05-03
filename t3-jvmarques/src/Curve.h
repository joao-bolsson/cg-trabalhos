#ifndef __CURVE_H
#define __CURVE_H

#include "Shape.h"
#include <vector>

using namespace std;

class Curve : public Shape {

private:
    vector<Point *> controlPoints;
    bool showingGraphControl = false;

public:
    /**
     * Creates a curve.
     */
    Curve();

    /**
     * @return The curve control points.
     */
    vector<Point *> getControlPts();

    /**
     * Adds a control point.
     * @param p Control point to add.
     */
    void addPoint(Point *p);

    /**
     * Changes a control point.
     * @param i Control point number.
     * @param x New x coordinate.
     * @param y New y coordinate
     */
    void changePoint(int i, int x, int y);

    void draw(Canvas *canvas);

    void drawSelectionBox(Canvas *canvas);

    bool isSelected(Point x);

    void translate(int x, int y);

    void rotate(bool d);

    Shape *copy();

    /**
     * @param p Selected point.
     * @return if p is  a control point - index of control point, else : -1.
     */
    int isSelectedPointCtrl(Point point);

    /**
     * Shows or not the control graph.
     */
    void showControlGraph(bool show);

    /**
     * Returns if the curve is showing its control graphic. 
     */
    bool isShowingControlGraph();
};

#endif
