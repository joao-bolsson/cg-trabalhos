#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Pixel.h"

// TODO: doc
class Image
{
private:
    Pixel **pixels;
    int width, height;

public:
    Image();
    Image(Pixel **pixels, unsigned width, unsigned height);
    int getWidth();
    int getHeight();
    void render();
};

#endif
