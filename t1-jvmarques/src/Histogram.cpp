#include "Histogram.h"
#include "gl_canvas2d.h"

Histogram::Histogram(Image *img, int x, int y, unsigned width, unsigned height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->img = img;
}

void Histogram::render() {
    // draw axis
    color(0, 0, 0);
    line(x, y, x + width, y);  // x axis
    rect(x, y, x, y + height); // y axis

    // Pixel **pixels = img->getPixels();
    // for (int y = 0; y < height; y++) {
    //     for (int x = 0; x < width; x++) {
    //     }
    // }
}