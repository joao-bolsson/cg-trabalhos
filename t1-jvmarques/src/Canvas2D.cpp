#include "Canvas2D.h"
#include <GL/glut.h>

static Canvas2D *INSTANCE;

Canvas2D::Canvas2D() {
    INSTANCE = this;
}

Canvas2D::~Canvas2D() {
    INSTANCE = NULL;
}

void Canvas2D::point(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}

void Canvas2D::line(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void Canvas2D::rect(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINE_LOOP);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);
    glEnd();
}

void Canvas2D::rectFill(int x1, int y1, int x2, int y2) {
    glBegin(GL_QUADS);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);
    glEnd();
}

void Canvas2D::polygon(float vx[], float vy[], int elems) {
    int cont;
    glBegin(GL_LINE_LOOP);
    for (cont = 0; cont < elems; cont++) {
        glVertex2d(vx[cont], vy[cont]);
    }
    glEnd();
}

void Canvas2D::polygonFill(float vx[], float vy[], int elems) {
    int cont;
    glBegin(GL_POLYGON);
    for (cont = 0; cont < elems; cont++) {
        glVertex2d(vx[cont], vy[cont]);
    }
    glEnd();
}

void Canvas2D::text(int x, int y, const char *t) {
    int tam = (int)strlen(t);
    for (int c = 0; c < tam; c++) {
        glRasterPos2i(x + c * 10, y);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);
    }
}

void Canvas2D::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1);
}

void Canvas2D::circle(int x, int y, int raio, int div) {
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

void Canvas2D::circleFill(int x, int y, int raio, int div) {
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

void Canvas2D::color(float r, float g, float b) {
    glColor3d(r, g, b);
}

void callSpecial(int key, int, int) {
    INSTANCE->keyboard(key + 100);
}

void callSpecialUp(int key, int, int) {
    INSTANCE->keyboardUp(key + 100);
}

void callKeyb(unsigned char key, int, int) {
    INSTANCE->keyboard(key);
}

void Canvas2D::keyboard(int key) {
    printf("\nTecla: %d", key);
    if (key < 200) {
        // opcao = key;
    }

    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void Canvas2D::mouse(int button, int state, int wheel, int direction, int x, int y) {
    this->mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    this->mouseY = y;

    if (state == 0) {
        // TODO: verificar se o x, y está sobre algum botao, se está, chamar bt->doClick()
    }
}

//funcao chamada toda vez que uma tecla for liberada
void Canvas2D::keyboardUp(int key) {
    printf("\nLiberou: %d", key);
}

void callKeybUp(unsigned char key, int, int) {
    INSTANCE->keyboardUp(key);
}

void callMouseClick(int button, int state, int x, int y) {
    INSTANCE->ConvertMouseCoord(button, state, -2, -2, x, y);
}

void callMouseWheelCB(int wheel, int direction, int x, int y) {
    INSTANCE->ConvertMouseCoord(-2, -2, wheel, direction, x, y);
}

void callMotion(int x, int y) {
    INSTANCE->ConvertMouseCoord(-2, -2, -2, -2, x, y);
}

void Canvas2D::ConvertMouseCoord(int button, int state, int wheel, int direction, int x, int y) {
#if Y_CANVAS_CRESCE_PARA_CIMA == TRUE
    y = *scrHeight - y; //deve-se inverter a coordenada y do mouse se o y da canvas crescer para cima. O y do mouse sempre cresce para baixo.
#else
    //nao faz nada.
#endif
    mouse(button, state, wheel, direction, x, y);
}

//funcao chamada sempre que a tela for redimensionada.
void Canvas2D::reshape(int w, int h) {
    *this->scrHeight = h; //atualiza as variaveis da main() com a nova dimensao da tela.
    *this->scrWidth = w;

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

void callBackReshape(int w, int h) {
    INSTANCE->reshape(w, h);
}

//definicao de valores para limpar buffers
void Canvas2D::inicializa() {
    glClearColor(1, 1, 1, 1);
    glPolygonMode(GL_FRONT, GL_FILL);
}

void Canvas2D::render() {
    // TODO
    clear(1, 1, 1);
}

void Canvas2D::display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    this->render();

    glFlush();
    glutSwapBuffers();
}

void callDisplay() {
    INSTANCE->display();
}

////////////////////////////////////////////////////////////////////////////////////////
//  inicializa o OpenGL
////////////////////////////////////////////////////////////////////////////////////////
void Canvas2D::initCanvas(int *w, int *h, const char *title) {
    int argc = 0;
    glutInit(&argc, NULL);

    scrHeight = h;
    scrWidth = w;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(*w, *h);
    glutInitWindowPosition(200, 200);
    glutCreateWindow(title);

    inicializa();

    glutReshapeFunc(callBackReshape);
    glutDisplayFunc(callDisplay);
    glutKeyboardFunc(callKeyb);
    glutKeyboardUpFunc(callKeybUp);
    glutSpecialUpFunc(callSpecialUp);
    glutSpecialFunc(callSpecial);

    glutIdleFunc(callDisplay);
    glutMouseFunc(callMouseClick);
    glutPassiveMotionFunc(callMotion);
    glutMotionFunc(callMotion);
    glutMouseWheelFunc(callMouseWheelCB);

    printf("GL Version: %s", glGetString(GL_VERSION));
}

void Canvas2D::runCanvas() {
    glutMainLoop();
}
