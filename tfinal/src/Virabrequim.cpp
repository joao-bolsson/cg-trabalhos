#include "Virabrequim.h"

/** 
 * TODO: construir todos os objetos na origem e depois transladar?
 * 
 * @param  radius: Radius.
 * @param  length: Length.
 * @param  center: Ponto onde vai ser construído.
 */
Virabrequim::Virabrequim(int radius, int length, Point center) : Object(center) {
    this->radius = radius;
    this->length = length;
    // calcula ponto para conexão com a biela
    float xPt = length * cos(angX) + center.getY();
    float yPt = length * sin(angX) + center.getY();
    float zPt = center.getZ();

    ptConnection = Point(xPt, yPt, zPt);

    // constroi o cilindro
    // TODO: faz do center até o ptConnection

    float step = 0.35; // 20 graus

    float height = length;

    float yBegin = center.getY();

    for (int h = 0; h <= height; h += 10) {
        vector<Point> line;
        for (float teta = 0; teta <= 2 * PI; teta += step) {
            float x = radius * sin(teta);
            float y = yBegin + h;
            float z = radius * cos(teta);

            Point p = Point(x, y, z);

            line.push_back(p);
        }
        points.push_back(line);
    }

    transform();
}

void Virabrequim::render() {
    if (1 > 0) {
        color(1, 0, 0);
        // TODO: precisar transformar o center?
        float xVirabrequim = ptConTransformed.getX(); // ja esta transformado: rotacionado e transladado
        float yVirabrequim = ptConTransformed.getY();
        // ponto central FIXO transladado
        circle(centerTransformed.getX(), centerTransformed.getY(), 3, 10);

        line(xVirabrequim, yVirabrequim, centerTransformed.getX(), centerTransformed.getY());
        circle(xVirabrequim, yVirabrequim, 3, 10);
        return;
    }

    ///////////// mesmo codigo de cylinder::render
    for (unsigned int l = 0; l < transformed.size(); l++) {
        color(1, 0, 0);
        vector<Point> points = transformed[l];
        float r = 0.1, g = 0.2, b = 0.3;
        for (unsigned int c = 0; c < points.size() - 1; c++) {
            Point p1 = points[c];
            Point p2 = points[c + 1];

            line(p1.getX(), p1.getY(), p2.getX(), p2.getY());

            if (l < transformed.size() - 1) {
                color(r, g, b);
                p2 = transformed[l + 1][c];
                line(p1.getX(), p1.getY(), p2.getX(), p2.getY());

                p2 = transformed[l + 1][c + 1];
                line(p1.getX(), p1.getY(), p2.getX(), p2.getY());
            }
            r += 0.02;
            g += 0.01;
            b += 0.02;
        }
        // connect the last with the first
        Point first = points[0];
        Point last = points[points.size() - 1];
        line(first.getX(), first.getY(), last.getX(), last.getY());

        if (l < transformed.size() - 1) {
            last = transformed[l + 1][0];
            line(first.getX(), first.getY(), last.getX(), last.getY());

            int size = transformed[l + 1].size();
            last = transformed[l + 1][size - 1];
            line(first.getX(), first.getY(), last.getX(), last.getY());
        }
    }
    //////////////////
}

void Virabrequim::transform() {
    float ang = 0; // angulo inicial do virabrequim com o eixo x
    float xPt = length * cos(ang) + center.getX();
    float yPt = length * sin(ang) + center.getY();
    float zPt = length * tan(ang) + center.getZ();

    ptConnection = Point(xPt, yPt, zPt);

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
    return ptConTransformed;
}