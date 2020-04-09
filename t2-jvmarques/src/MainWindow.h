#ifndef __MAINWINDOW__H__
#define __MAINWINDOW__H__

#include "Canvas.h"

class MainWindow {

private:
    int width, height;
    char *title;

public:
    MainWindow(int width, int height, char *title);
    ~MainWindow();

    void init();
    void show();
};

#endif