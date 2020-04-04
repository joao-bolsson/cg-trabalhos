#include "Histogram.h"
#include "gl_canvas2d.h"

Histogram::Histogram(Image *img, int x, int y, unsigned width, unsigned height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->img = img;
    numMaxPixels = img->getHeight() * img->getWidth();
    init();
}

void Histogram::init() {
    Pixel **pixels = img->getPixels();

    for (int y = 0; y < img->getHeight(); y++) {
        for (int x = 0; x < img->getWidth(); x++) {
            Pixel p = pixels[y][x];
            int r = p.getRed() * 255;
            int g = p.getGreen() * 255;
            int b = p.getBlue() * 255;

            // never must happen, but just to avoid index out of bounds anyway
            if (r >= 0 && r < ARRAY_CHANNEL_SIZE) {
                red[r]++;
            }

            if (g >= 0 && g < ARRAY_CHANNEL_SIZE) {
                green[r]++;
            }

            if (b >= 0 && b < ARRAY_CHANNEL_SIZE) {
                blue[r]++;
            }
        }
    }
}

void Histogram::plotChannel(int *channel, unsigned size) {
    for (int i = 0; i < size; i++) {
        int coordX = i * width / (ARRAY_CHANNEL_SIZE - 1);
        int coordY = channel[i] * height / numMaxPixels;

        rect(this->x + coordX, this->y, this->x + coordX, this->y + coordY);
    }
}

void Histogram::render() {
    // draw axis
    color(0, 0, 0);
    line(x, y, x + width, y);  // x axis
    rect(x, y, x, y + height); // y axis

    color(1, 0, 0);
    plotChannel(red, ARRAY_CHANNEL_SIZE);

    color(0, 1, 0);
    plotChannel(green, ARRAY_CHANNEL_SIZE);

    color(0, 0, 1);
    plotChannel(blue, ARRAY_CHANNEL_SIZE);
}