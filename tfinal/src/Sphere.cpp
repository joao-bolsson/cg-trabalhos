#include "Sphere.h"
#include "gl_canvas2d.h"

Sphere::Sphere(float radius) {
    this->radius = radius;

    float x, y, z;
    float step = PI / FACTOR_RAD;
    int l = 0, c = 0;
    for (float teta = 0; teta <= 2 * PI; teta += step) {
        for (float fi = 0; fi <= PI; fi += step) {
            x = radius * cos(teta) * cos(fi);
            z = radius * sin(teta) * cos(fi);
            y = radius * sin(fi);

            mat[l][c++] = Point(x, y, z);
        }
        l++;
    }
}

Point Sphere::translate(Point p) {
    float x = p.getX();
    float y = p.getY() + 10;
    float z = p.getZ() - 12;

    return Point(x, y, z);
}

Point Sphere::project(Point p) {
    float d = -10.0;

    float x = (p.getX() * d) / p.getZ();
    float y = (p.getY() * d) / p.getZ();
    float z = 0;

    return Point(x, y, z);
}

Point Sphere::rotateX(Point p) {
    ang += 0.00001;

    float x = p.getX();
    float y = cos(ang) * p.getY() - sin(ang) * p.getZ();
    float z = sin(ang) * p.getY() + cos(ang) * p.getZ();

    return Point(x, y, z);
}

void Sphere::transform() {
    Point p;
    //Processa cada vertice da superficie individualmente.
    for (int x = 0; x <= DIMX; x++) {
        for (int z = 0; z <= DIMY; z++) {
            //copia os pontos originais
            p = mat[x][z];

            //rotacao no eixo x
            // p = rotateX(p);

            //translacao no eixo z
            p = translate(p);

            //projecao em perspectiva
            transf[x][z] = project(p);
        }
    }
}

void Sphere::render() {

    transform();

    color(1, 0, 0);

    for (int l = 0; l < DIMX; l++) {
        for (int c = 0; c < DIMY; c++) {
            line(transf[l][c].getX(), transf[l][c].getY(), transf[l][c + 1].getX(), transf[l][c + 1].getY());
            line(transf[l][c].getX(), transf[l][c].getY(), transf[l + 1][c].getX(), transf[l + 1][c].getY());
            line(transf[l][c].getX(), transf[l][c].getY(), transf[l + 1][c + 1].getX(), transf[l][c + 1].getY());
        }
    }
}
