#ifndef __POINT_H
#define __POINT_H

class Point {
private:
    int x, y;

public:
    /**
     * Default point (0, 0).
     */
    Point();

    /**
     * Default construct.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    Point(int x, int y);

    /**
     * @return The x coordinate.
     */
    int getX() const;

    /**
     * Sets the x coordinate.
     * @param x coordinate to sets.
     */
    void setX(int x);

    /**
     * Sets the y coordinate.
     * @param y coordinate to sets.
     */
    void setY(int y);

    /**
     * @return The y coordinate.
     */
    int getY() const;
};

#endif
