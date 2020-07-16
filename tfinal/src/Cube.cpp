#include "Cube.h"
#include "gl_canvas2d.h"

Cube::Cube(int size, float x, float y, float z) {
    this->l = size;

    // z+ para dentro da tela

    front[0][0] = Point(x, y, z);         // 1
    front[0][1] = Point(x + l, y, z);     // 2
    front[1][0] = Point(x, y + l, z);     // 3
    front[1][1] = Point(x + l, y + l, z); // 4

    back[0][0] = Point(x, y, z - l);         // 5
    back[0][1] = Point(x + l, y, z - l);     // 6
    back[1][0] = Point(x, y + l, z - l);     // 7
    back[1][1] = Point(x + l, y + l, z - l); // 8

    int i = 1;
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            Point p = front[x][y];
            printf("ponto %d (%.1f, %.1f, %.1f)\n", i++, p.getX(), p.getY(), p.getZ());
        }
    }
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            Point p = back[x][y];
            printf("ponto %d (%.1f, %.1f, %.1f)\n", i++, p.getX(), p.getY(), p.getZ());
        }
    }
}

void Cube::transform() {
    //Processa cada vertice da superficie individualmente.
    for (int x = 0; x < 2; x++) {
        for (int z = 0; z < 2; z++) {
            frontTransf[x][z] = front[x][z].copy();
            frontTransf[x][z].transform(distance, angX, angY, 300, 300);

            //// QUADRADO DE TRÁS

            backTransf[x][z] = back[x][z].copy();
            backTransf[x][z].transform(distance, angX, angY, 300, 300);
        }
    }
}

void Cube::setDistance(int d) {
    this->distance = d;
}

void Cube::setAngX(float ang) {
    this->angX = ang;
}

void Cube::setAngY(float ang) {
    this->angY = ang;
}

void Cube::setAngZ(float ang) {
    this->angZ = ang;
}

float Cube::getAngX() {
    return angX;
}

float Cube::getAngY() {
    return angY;
}

float Cube::getAngZ() {
    return angZ;
}

int Cube::getDistance() {
    return distance;
}

void Cube::render() {
    color(1, 0, 0);

    transform();

    line(frontTransf[0][0].getX(), frontTransf[0][0].getY(), frontTransf[0][1].getX(), frontTransf[0][1].getY()); // 1-2
    line(frontTransf[0][0].getX(), frontTransf[0][0].getY(), frontTransf[1][0].getX(), frontTransf[1][0].getY()); // 1-3
    line(frontTransf[0][0].getX(), frontTransf[0][0].getY(), backTransf[0][0].getX(), backTransf[0][0].getY());   // 1-5

    line(frontTransf[0][1].getX(), frontTransf[0][1].getY(), frontTransf[1][1].getX(), frontTransf[1][1].getY()); // 2-4
    line(frontTransf[0][1].getX(), frontTransf[0][1].getY(), backTransf[0][1].getX(), backTransf[0][1].getY());   // 2-6

    line(frontTransf[1][0].getX(), frontTransf[1][0].getY(), frontTransf[1][1].getX(), frontTransf[1][1].getY()); // 3-4
    line(frontTransf[1][0].getX(), frontTransf[1][0].getY(), backTransf[1][0].getX(), backTransf[1][0].getY());   // 3-7

    line(frontTransf[1][1].getX(), frontTransf[1][1].getY(), backTransf[1][1].getX(), backTransf[1][1].getY()); // 4-8

    color(0, 0, 1);
    line(backTransf[0][0].getX(), backTransf[0][0].getY(), backTransf[0][1].getX(), backTransf[0][1].getY()); // 5-6
    line(backTransf[0][0].getX(), backTransf[0][0].getY(), backTransf[1][0].getX(), backTransf[1][0].getY()); // 5-7
    line(backTransf[0][1].getX(), backTransf[0][1].getY(), backTransf[1][1].getX(), backTransf[1][1].getY()); // 6-8
    line(backTransf[1][0].getX(), backTransf[1][0].getY(), backTransf[1][1].getX(), backTransf[1][1].getY()); // 7-8
}
