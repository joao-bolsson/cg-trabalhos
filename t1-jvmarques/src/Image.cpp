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

void Image::renderPixelQuad(int x, int y) {
    if (pixelSize < 1) {
        // interpolação dos pixels vizinhos
        int r = 0, g = 0, b = 0;
        for (int i = 0; i < pixelSize; i++) {
            for (int j = 0; j < pixelSize; j++) {
                Pixel p = pixels[x + i][y + j];
                r = p.getRed();
                g = p.getGreen();
                b = p.getBlue();
            }
        }

        Pixel p = Pixel(r / 4, g / 4, b / 4);
        color(p.getRed(), p.getGreen(), p.getBlue());
        point(this->x + x * pixelSize, this->y + y * pixelSize);
    } else if (pixelSize > 1) {
        // replicação de cada pixel ao longos dos eixos x,y
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
        // desenha o pixel
        Pixel p = pixels[x][y];
        color(p.getRed(), p.getGreen(), p.getBlue());
        point(this->x + x, this->y + y);
    }
}

void Image::render() {
    int step = 1;
    if (pixelSize < 1) {
        step = 1 / pixelSize;
    }

    for (int y = 0; y < height; y += step) {
        for (int x = 0; x < width; x += step) {
            /**
             * Render each pixel accordingly with the scale.
             */
            renderPixelQuad(x, y);
        }
    }
}

void Image::scale(float factor) {
    pixelSize = factor;
}

float Image::getScale() {
    return pixelSize;
}
