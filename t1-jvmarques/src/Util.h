#ifndef ___UTIL__H___
#define ___UTIL__H___

#include "Pixel.h"

class Util
{
public:
    static Pixel **getImagePixels(unsigned char *imgData, unsigned width, unsigned height);
};

#endif
