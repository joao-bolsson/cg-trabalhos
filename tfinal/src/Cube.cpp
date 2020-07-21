#include "Cube.h"
#include "gl_canvas2d.h"

Cube::Cube(int size, Point center) : Object(center) {
    this->l = size;

    float x = center.getX();
    float y = center.getY();
    float z = center.getZ();

    float factor = l / 2;

    vector<Point> front;
    vector<Point> back;

    // z+ para dentro da tela

    front.push_back(Point(x - factor, y - factor, z - factor)); // 1
    front.push_back(Point(x + factor, y - factor, z - factor)); // 2
    front.push_back(Point(x + factor, y + factor, z - factor)); // 4
    front.push_back(Point(x - factor, y + factor, z - factor)); // 3

    back.push_back(Point(x - factor, y - factor, z + factor)); // 5
    back.push_back(Point(x + factor, y - factor, z + factor)); // 6
    back.push_back(Point(x + factor, y + factor, z + factor)); // 8
    back.push_back(Point(x - factor, y + factor, z + factor)); // 7

    points.push_back(front);
    points.push_back(back);

    transform();
}

void Cube::render() {
    color(1, 0, 0);

    for (unsigned int c = 0; c < transformed.size(); c++) {
        if (c > 0) {
            color(0, 0, 1);
        }
        auto pts = transformed[c];
        for (unsigned int i = 0; i < pts.size() - 1; i++) {
            Point p1 = pts[i];
            Point p2 = pts[i + 1];

            line(p1.getX(), p1.getY(), p2.getX(), p2.getY());

            if (c < transformed.size() - 1) {
                Point p2 = transformed[c + 1][i];
                line(p1.getX(), p1.getY(), p2.getX(), p2.getY());
            }
        }
        // connect the last with the first
        Point first = pts[0];
        Point last = pts[pts.size() - 1];
        line(first.getX(), first.getY(), last.getX(), last.getY());

        if (c < transformed.size() - 1) {
            Point last1 = pts[pts.size() - 1];
            Point last2 = transformed[c + 1][pts.size() - 1];
            line(last1.getX(), last1.getY(), last2.getX(), last2.getY());
        }
    }
}
