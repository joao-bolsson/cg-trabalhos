#include "Pixel.h"

Pixel::Pixel()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Pixel::Pixel(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

int Pixel::getRed()
{
    return r;
}

int Pixel::getGreen()
{
    return g;
}

int Pixel::getBlue()
{
    return b;
}