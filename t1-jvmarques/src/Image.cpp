// TODO: doc
#include "Image.h"
#include "gl_canvas2d.h"

Image::Image()
{
    // empty
}

Image::Image(Pixel **pixels, unsigned width, unsigned height)
{
    this->pixels = pixels;
    this->x = 0;
    this->y = 0;
    this->width = width;
    this->height = height;
}

Image::Image(Pixel **pixels, int x, int y, unsigned width, unsigned height)
{
    this->pixels = pixels;
    this->x = x;
    this->y = y;
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

int Image::getX()
{
    return x;
}

int Image::getY()
{
    return y;
}
void Image::render()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Pixel p = pixels[y][x];
            color(p.getRed(), p.getGreen(), p.getBlue());
            point(this->x + x, this->y + y);
        }
    }
}
