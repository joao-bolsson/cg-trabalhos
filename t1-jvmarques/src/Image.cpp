// TODO: doc
#include "Image.h"

Image::Image()
{
    // empty
}

Image::Image(Pixel **pixels, unsigned width, unsigned height)
{
    this->pixels = pixels;
    this->width = width;
    this->height = height;
}

int Image::getWidth()
{
    return width;
}
int Image::getHeight()
{
    return height;
}
void Image::render()
{
    // TODO
}
