#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

int tiempo = 600;
int segmentos = 4;

void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

void reshape(GLsizei w, GLsizei h) {
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, w, h);
}

void timer(int valor) {
    glutPostRedisplay();
    glutTimerFunc(tiempo, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float theta = 0;
    float x = 0, y = 0;

    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    for (int i = 0; i < segmentos;i++) {
        theta = 2*M_PI*float(i)/float(segmentos);
        x = 50*cosf(theta-glm::radians(45.0));
        y = 50 * sinf(theta - glm::radians(45.0));
        glVertex2f(x, y);
    }
    glEnd();
    segmentos += 1;


    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ejemplo morph");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
