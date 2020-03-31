#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include "Image.h"

class Histogram {
protected:
    int x, y;
    unsigned width, height;

private:
    Image *img;

public:
    Histogram(Image *img, int x, int y, unsigned width, unsigned height);
    void render();
};

#endif