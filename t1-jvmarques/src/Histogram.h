#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include "Image.h"

#define ARRAY_CHANNEL_SIZE 256

class Histogram {
protected:
    int x, y;
    unsigned width, height, numMaxPixels;
    int red[ARRAY_CHANNEL_SIZE] = {0};
    int green[ARRAY_CHANNEL_SIZE] = {0};
    int blue[ARRAY_CHANNEL_SIZE] = {0};

private:
    Image *img;

public:
    Histogram(Image *img, int x, int y, unsigned width, unsigned height);
    void init();
    void plotChannel(int *vect, unsigned size);
    void render();
};

#endif