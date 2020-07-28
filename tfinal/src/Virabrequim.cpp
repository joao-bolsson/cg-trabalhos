#include "Virabrequim.h"

/** 
 * 
 * @param  radius: Radius.
 * @param  length: Length.
 * @param  center: Ponto onde vai ser construído.
 */
Virabrequim::Virabrequim(int radius, int length, Point center) : Cylinder(radius, length, center, false) {
    // calcula ponto para conexão com a biela
    double ang = 0; // angulo inicial do virabrequim com o eixo x
    double xPt = length * cos(ang) + center.getX();
    double yPt = length * sin(ang) + center.getY();
    double zPt = length * tan(ang) + center.getZ();

    ptConnection = Point(xPt, yPt, zPt);
}

void Virabrequim::render() {
    if (1 > 2) { // desenha 2d
        color(1, 0, 0);
        // TODO: precisar transformar o center?
        double xVirabrequim = ptConTransformed.getX(); // ja esta transformado: rotacionado e transladado
        double yVirabrequim = ptConTransformed.getY();
        // ponto central FIXO transladado
        circle(centerTransformed.getX(), centerTransformed.getY(), 3, 10);

        line(xVirabrequim, yVirabrequim, centerTransformed.getX(), centerTransformed.getY());
        circle(xVirabrequim, yVirabrequim, 3, 10);
        return;
    }

    Cylinder::render();
}

void Virabrequim::transform() {
    Point p = ptConnection.copy();

    // move to origin
    p.translate(-center.getX(), -center.getY(), -center.getZ());

    p.rotateZ(angZ);
    p.rotateY(angY);
    p.rotateX(angX);

    p.translate(0, 0, 150);

    p.project(distance);

    // return back to the original center
    p.translate(center.getX(), center.getY(), center.getZ());

    // optional: centralizing in another point on screen
    p.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    ptConTransformed = p;

    Object::transform();
}

Point Virabrequim::getPtConnection() {
    return ptConnection;
}

Point Virabrequim::getPtConnectionTransf() {
    Point p = ptConnection.copy();
    p.translate(-center.getX(), -center.getY(), -center.getZ());

    p.rotateZ(angZ);
    p.rotateY(angY);
    p.rotateX(angX);

    // return back to the original center
    p.translate(center.getX(), center.getY(), center.getZ());
    return p;
}
