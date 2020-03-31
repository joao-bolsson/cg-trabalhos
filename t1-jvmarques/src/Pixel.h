#ifndef PIXEL_INCLUDED
#define PIXEL_INCLUDED

// TODO: doc
class Pixel {
private:
    int r, g, b;

public:
    Pixel();
    Pixel(int r, int g, int b);
    int getRed();
    int getGreen();
    int getBlue();

    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);
};

#endif
