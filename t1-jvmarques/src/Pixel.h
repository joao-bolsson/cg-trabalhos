#ifndef PIXEL_INCLUDED
#define PIXEL_INCLUDED

class Pixel {
private:
    float r, g, b;

public:
    Pixel();
    Pixel(float r, float g, float b);
    float getRed();
    float getGreen();
    float getBlue();

    void setRed(float r);
    void setGreen(float g);
    void setBlue(float b);
};

#endif
