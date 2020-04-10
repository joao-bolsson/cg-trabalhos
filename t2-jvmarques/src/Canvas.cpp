#include "Canvas.h"

int *scrWidth, *scrHeight; //guarda referencia para as variaveis de altura e largura da main()

Canvas::Canvas() {
}

Canvas::~Canvas() {
}

void Canvas::setWindow(MainWindow *window) {
    this->window = window;
}

void Canvas::point(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}

void Canvas::line(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void Canvas::rect(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINE_LOOP);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);
    glEnd();
}

void Canvas::rectFill(int x1, int y1, int x2, int y2) {
    glBegin(GL_QUADS);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);
    glEnd();
}

void Canvas::polygon(float vx[], float vy[], int elems) {
    int cont;
    glBegin(GL_LINE_LOOP);
    for (cont = 0; cont < elems; cont++) {
        glVertex2d(vx[cont], vy[cont]);
    }
    glEnd();
}

void Canvas::polygonFill(float vx[], float vy[], int elems) {
    int cont;
    glBegin(GL_POLYGON);
    for (cont = 0; cont < elems; cont++) {
        glVertex2d(vx[cont], vy[cont]);
    }
    glEnd();
}

void Canvas::text(int x, int y, const char *t) {
    int tam = (int)strlen(t);
    for (int c = 0; c < tam; c++) {
        glRasterPos2i(x + c * 10, y);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);
    }
}

void Canvas::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1);
}

void Canvas::circle(int x, int y, int raio, int div) {
    float ang, x1, y1;
    float inc = PI_2 / div;
    glBegin(GL_LINE_LOOP);
    for (ang = 0; ang < 6.27; ang += inc) //nao vai ateh PI_2 pois o ultimo ponto eh fechado automaticamente com o primeiro, pois tem o tipo LINE_LOOP
    {
        x1 = (cos(ang) * raio);
        y1 = (sin(ang) * raio);
        glVertex2d(x1 + x, y1 + y);
    }
    glEnd();
}

void Canvas::circleFill(int x, int y, int raio, int div) {
    float ang, x1, y1;
    float inc = PI_2 / div;
    glBegin(GL_POLYGON);
    for (ang = 0; ang < 6.27; ang += inc) {
        x1 = (cos(ang) * raio);
        y1 = (sin(ang) * raio);
        glVertex2d(x1 + x, y1 + y);
    }
    glEnd();
}

void Canvas::color(float r, float g, float b) {
    glColor3d(r, g, b);
}

void Canvas::mouse(int bt, int st, int wheel, int direction, int x, int y) {
    mouseX = x;
    mouseY = y;
}

Point Canvas::getMousePoint() {
    return Point(mouseX, mouseY);
}

void Canvas::keyboard(int key) {
    // TODO
}

void Canvas::keyboardUp(int key) {
    // TODO
}

void Canvas::mouseClick(int button, int state, int x, int y) {
    ConvertMouseCoord(button, state, -2, -2, x, y);
}

void Canvas::mouseWheelCB(int wheel, int direction, int x, int y) {
    ConvertMouseCoord(-2, -2, wheel, direction, x, y);
}

void Canvas::ConvertMouseCoord(int button, int state, int wheel, int direction, int x, int y) {
#if Y_CANVAS_CRESCE_PARA_CIMA == TRUE
    y = *scrHeight - y; //deve-se inverter a coordenada y do mouse se o y da canvas crescer para cima. O y do mouse sempre cresce para baixo.
#else
    //nao faz nada.
#endif
    mouse(button, state, wheel, direction, x, y);
}

//funcao chamada sempre que a tela for redimensionada.
void Canvas::reshape(int w, int h) {
    *scrHeight = h; //atualiza as variaveis da main() com a nova dimensao da tela.
    *scrWidth = w;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //cria uma projecao ortografica com z entre (-1, 1).
#if Y_CANVAS_CRESCE_PARA_CIMA == TRUE
    //parametros: left, right, bottom, top
    gluOrtho2D(0.0, w, 0.0, h); //o eixo y cresce para cima.
#else
    //parametros: left, right, bottom, top
    gluOrtho2D(0.0, w, h, 0.0); //o eixo y cresce para baixo
#endif

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//definicao de valores para limpar buffers
void Canvas::inicializa() {
    glClearColor(1, 1, 1, 1);
    glPolygonMode(GL_FRONT, GL_FILL);
}

void Canvas::render() {
    if (window != NULL) {
        window->renderComponents();
    }
}

void Canvas::display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    render();

    glFlush();
    glutSwapBuffers();
}

void Canvas::initCanvas(int *w, int *h, const char *title) {
    int argc = 0;
    glutInit(&argc, NULL);

    scrHeight = h;
    scrWidth = w;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(*w, *h);
    glutInitWindowPosition(200, 200);
    glutCreateWindow(title);

    inicializa();

    printf("GL Version: %s", glGetString(GL_VERSION));
}

void Canvas::runCanvas() {
    glutMainLoop();
}
