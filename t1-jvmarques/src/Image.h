#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Pixel.h"

// TODO: doc
class Image {
private:
    Pixel **pixels;
    int x, y, width, height;

public:
    Image();
    Image(Pixel **pixels, unsigned width, unsigned height);
    Image(Pixel **pixels, int x, int y, unsigned width, unsigned height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void render();
};

#endif
