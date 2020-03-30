// TODO: doc
#include "Image.h"
#include "gl_canvas2d.h"

Image::Image() {
    // empty
}

Image::Image(Pixel **pixels, unsigned width, unsigned height) {
    this->pixels = pixels;
    this->x = 0;
    this->y = 0;
    this->width = width;
    this->height = height;
    this->originalWidth = width;
    this->originalHeight = height;
}

Image::Image(Pixel **pixels, int x, int y, unsigned width, unsigned height) {
    this->pixels = pixels;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->originalWidth = width;
    this->originalHeight = height;
}

int Image::getWidth() {
    return width;
}
int Image::getHeight() {
    return height;
}

int Image::getX() {
    return x;
}

int Image::getY() {
    return y;
}

Pixel Image::getPixelQuad(int x, int y) {
    int r = 0, g = 0, b = 0;

    // TODO: render pixel x, y
    if (pixelSize < 1) {
        // TODO: faz a interpolação
    } else if (pixelSize > 1) {
        // duplica cada pixel no x e y
        Pixel p = pixels[x][y];
        color(p.getRed(), p.getGreen(), p.getBlue());

        int coordX = this->x + x;
        int coordY = this->y + y;

        for (int i = 0; i < pixelSize; i++) {
            for (int j = 0; j < pixelSize; j++) {
                point(coordX * pixelSize + i, coordY * pixelSize + j);
            }
        }
    } else {
        Pixel p = pixels[x][y];
        color(p.getRed(), p.getGreen(), p.getBlue());
        point(this->x + x, this->y + y);
    }

    return Pixel(r, g, b);
}

void Image::render() {
    bool zoomIn = pixelSize > 1;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            getPixelQuad(x, y);

            // Pixel p = pixels[y][x];
            // color(p.getRed(), p.getGreen(), p.getBlue());
            //
            // if (pixelSize == 1) {
            //     point(this->x + x, this->y + y);
            // } else if (zoomIn) {
            //     for (int i = 0; i < pixelSize; i++) {
            //         for (int j = 0; j < pixelSize; j++) {
            //             point(this->x + x + i, this->y + y + j);
            //         }
            //     }
            // }
        }
    }
}

void Image::scale(float factor) {
    pixelSize = factor;
}

float Image::getScale() {
    return pixelSize;
}
