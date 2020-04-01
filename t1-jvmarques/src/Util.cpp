#include "Util.h"
#include <stdio.h>

Pixel **Util::getImagePixels(unsigned char *imgData, unsigned width, unsigned height) {
    Pixel **pixels;
    pixels = new Pixel *[height];

    int bytesPerLine = width * 3;
    for (unsigned int y = 0; y < height; y++) {
        pixels[y] = new Pixel[width];

        for (unsigned int x = 0, w = 0; x < width * 3; x += 3, w++) {
            int pos = y * bytesPerLine + x;

            int r = imgData[pos];
            int g = imgData[pos + 1];
            int b = imgData[pos + 2];

            pixels[y][w] = Pixel(r / 255.0, g / 255.0, b / 255.0);
        }
    }

    return pixels;
}
