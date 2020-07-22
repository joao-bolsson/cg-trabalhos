#ifndef BIELA_H_INCLUDED
#define BIELA_H_INCLUDED

#include "Object.h"

class Biela : public Object {
private:
    Point pVirabrequim;

public:
    Biela(Point center);

    void render();
    void transform();

    /**
     * Connect this object with the given point and inclinates it in x axis.
     *    
     * @param  ptConnection: Point to connect with the virabrequim.
     * @param  ang: Inclination angle.
     */
    void connect(Point ptConnection, float ang);

    Point getConnectionPistao();
};

#endif