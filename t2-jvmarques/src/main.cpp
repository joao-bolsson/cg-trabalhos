#include "MainWindow.h"

int screenWidth = 800, screenHeight = 500;

int main() {
    MainWindow *window = new MainWindow(screenWidth, screenHeight, "Trabalho 2");
    window->show();
}
