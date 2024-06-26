#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Pixel.h"

class Image {
private:
    Pixel **pixels;
    int x, y, originalWidth, originalHeight, width, height;
    float pixelSize = 1;

    float redChannel = 0, greenChannel = 0, blueChannel = 0;
    bool luminance = false;
    int countRotateRight = 0;

public:
    Image();
    Image(Pixel **pixels, unsigned width, unsigned height);
    Image(Pixel **pixels, int x, int y, unsigned width, unsigned height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    Pixel **getPixels();
    void render();
    void scale(float factor);
    float getScale();

    /**
     * The image is drawn based on its width and height, pixel by pixel. 
     * This method draw the pixel at point (x, y) of the image, based on its scale.
     * If scale is greater than 1 then each pixel is replicated along x and y axis accordingly with the 
     * image scale and the dimensions.
     * 
     * If scale is lower than 1 then the interpolation method is used to decide the color of the quadrant.
     * 
     * If scale is 1 then the image will be drawn with the original size pixel by pixel.
     * 
     * If scale is greater than 1 then each pixel will be extended to the neighboors positions.
     */
    void renderPixelQuad(int lineIndex, int colIndex, int x, int y, bool swapAxis);

    void rotateLeft();
    void rotateRight();

    void turnRedChannel();
    void turnGreenChannel();
    void turnBlueChannel();

    void setColor(Pixel p);
    void turnLuminance();
};

#endif
