#ifndef __MAINWINDOW__H__
#define __MAINWINDOW__H__

class MainWindow {

private:
    int width, height;
    char *title;

public:
    MainWindow(int width, int height, char *title);
    ~MainWindow();

    void renderComponents();
    void init();
    void show();
};

#endif