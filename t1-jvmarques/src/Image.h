#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Pixel.h"

// TODO: doc
class Image {
private:
    Pixel **pixels;
    int x, y, originalWidth, originalHeight, width, height;
    float pixelSize = 1;

public:
    Image();
    Image(Pixel **pixels, unsigned width, unsigned height);
    Image(Pixel **pixels, int x, int y, unsigned width, unsigned height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void render();
    void scale(float factor);
    float getScale();
    Pixel getPixelQuad(int x, int y);
};

#endif
