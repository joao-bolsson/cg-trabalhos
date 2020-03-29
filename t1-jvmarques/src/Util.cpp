#include "Util.h"
#include <stdio.h>

Pixel **Util::getImagePixels(unsigned char *imgData, unsigned width, unsigned height)
{
    Pixel **pixels;
    pixels = new Pixel *[height];

    for (int y = 0; y < height; y++)
    {
        pixels[y] = new Pixel[width];
        for (int x = 0, w = 0; x < width * 3; x += 3, w++)
        {
            int r = imgData[x];
            int g = imgData[x + 1];
            int b = imgData[x + 2];

            pixels[y][w] = Pixel(r, g, b);
        }
    }
    return pixels;
}
