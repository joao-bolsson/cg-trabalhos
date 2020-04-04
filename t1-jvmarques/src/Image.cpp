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

Pixel **Image::getPixels() {
    return pixels;
}

void Image::turnRedChannel() {
    redChannel = redChannel == 0 ? 1 : 0;
}

void Image::turnGreenChannel() {
    greenChannel = greenChannel == 0 ? 1 : 0;
}

void Image::turnBlueChannel() {
    blueChannel = blueChannel == 0 ? 1 : 0;
}

void Image::setColor(Pixel pixel) {
    Pixel p = Pixel(pixel.getRed() * redChannel,
                    pixel.getGreen() * greenChannel,
                    pixel.getBlue() * blueChannel);

    if (luminance) {
        float y = 0.299 * p.getRed() + 0.587 * p.getGreen() + 0.114 * p.getBlue();
        color(y, y, y);
    } else {
        color(p.getRed(), p.getGreen(), p.getBlue());
    }
}

void Image::turnLuminance() {
    luminance = !luminance;
}

void Image::renderPixelQuad(int lineIndex, int colIndex, int x, int y, bool swapAxis) {
    if (pixelSize < 1) {
        // interpolação dos pixels vizinhos
        int r = 0, g = 0, b = 0;
        int num = 0;
        for (int i = 0; i < pixelSize; i++) {
            for (int j = 0; j < pixelSize; j++) {
                Pixel p = pixels[lineIndex + i][colIndex + j];
                r = p.getRed();
                g = p.getGreen();
                b = p.getBlue();
                num++;
            }
        }

        Pixel p = Pixel(r / num, g / num, b / num);
        setColor(p);
        point(this->x + x * pixelSize, this->y + y * pixelSize);
    } else if (pixelSize > 1) {
        // replicação de cada pixel ao longos dos eixos x,y
        Pixel p = pixels[lineIndex][colIndex];
        setColor(p);

        int coordX = this->x + x;
        int coordY = this->y + y;

        for (int i = 0; i < pixelSize; i++) {
            for (int j = 0; j < pixelSize; j++) {
                if (swapAxis && 1 < 0) {
                    point(coordY * pixelSize + j, coordX * pixelSize + i);
                } else {
                    point(coordX * pixelSize + i, coordY * pixelSize + j);
                }
            }
        }
    } else {
        // desenha o pixel
        Pixel p = pixels[lineIndex][colIndex];
        setColor(p);
        if (swapAxis) {
            point(this->y + y, this->x + x);
        } else {
            point(this->x + x, this->y + y);
        }
    }
}

void Image::rotateRight() {
    if (countRotateRight + 1 == 4) {
        countRotateRight = 0;
    } else {
        countRotateRight++;
    }
}

void Image::rotateLeft() {
    if (countRotateRight - 1 < 0) {
        countRotateRight = (countRotateRight - 1) + 4;
    } else {
        countRotateRight--;
    }
}

void Image::render() {
    int step = 1;
    if (pixelSize < 1) {
        step = 1 / pixelSize;
    }

    if (countRotateRight == 3) {
        for (int l = height - 1, coordY = 0; l >= 0; l -= step, coordY += step) {
            for (int c = 0, coordX = 0; c < width; c += step, coordX += step) {
                renderPixelQuad(l, c, coordX, coordY, true);
            }
        }
    } else if (countRotateRight == 1) {
        for (int l = 0, coordY = 0; l < height; l += step, coordY += step) {
            for (int c = width, coordX = 0; c >= 0; c -= step, coordX += step) {
                renderPixelQuad(l, c, coordX, coordY, true);
            }
        }
    } else if (countRotateRight == 2) {
        for (int l = height - 1, coordY = 0; l >= 0; l -= step, coordY += step) {
            for (int c = width, coordX = 0; c >= 0; c -= step, coordX += step) {
                renderPixelQuad(l, c, coordX, coordY, false);
            }
        }
    } else {
        for (int l = 0, coordY = 0; l < height; l += step, coordY += step) {
            for (int c = 0, coordX = 0; c < width; c += step, coordX += step) {
                renderPixelQuad(l, c, coordX, coordY, false);
            }
        }
    }
}

void Image::scale(float factor) {
    pixelSize = factor;
}

float Image::getScale() {
    return pixelSize;
}
