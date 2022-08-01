#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

int width, height;
int isFullscreen = 0;

void display2();
void drawCube(float alpha);
void reshape2(int w, int h);
void keyboard(unsigned char key, int x, int y);
void checkFullscreen();

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    //glutInitWindowPosition(100,100);
    //glutInitWindowSize(1000,600);

    glutCreateWindow("Ejemplo");
    glutReshapeWindow(1000, 600);
    glutPositionWindow(100, 100);

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display2);
    glutReshapeFunc(reshape2);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'f':
    case 'F':
        checkFullscreen();
        break;
    case 'q':
    case 'Q':
        if (isFullscreen)
            glutLeaveFullScreen();
        exit(0);
        break;
    case 'e':
    case 'E':
        //glutLeaveFullScreen();
        checkFullscreen();
        break;
    default:
        break;
    }
}

void checkFullscreen() {
    if (isFullscreen) {
        //cambiar a pequeña
        glutLeaveFullScreen();
        glutReshapeWindow(1000, 600);
        glutPositionWindow(100, 100);
        display2();
    }
    else {
        //full screen
        glutGameModeString("640x480:60");
        glutEnterGameMode();
        glEnable(GL_DEPTH_TEST);
        glutDisplayFunc(display2);
        glutReshapeFunc(reshape2);
        glutKeyboardFunc(keyboard);
    }
    isFullscreen = !isFullscreen;
}

void drawCube(float alpha) {
    /* A step backward, then spin the cube */
    glTranslatef(0, 0, -10);
    glRotatef(30, 1, 0, 0);
    glRotatef(alpha, 0, 1, 0);
    glScalef(0.8, 0.8, 0.8);
    /* We tell we want to draw quads */
    glBegin(GL_QUADS);

    /* Every four calls to glVertex, a quad is drawn */
    glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
    glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
    glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
    glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);

    glColor3f(1, 0, 0); glVertex3f(1, -1, -1);
    glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
    glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
    glColor3f(1, 1, 0); glVertex3f(1, 1, -1);

    glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
    glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
    glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
    glColor3f(1, 0, 0); glVertex3f(1, -1, -1);

    glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);
    glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
    glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
    glColor3f(1, 1, 0); glVertex3f(1, 1, -1);

    glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
    glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);
    glColor3f(1, 1, 0); glVertex3f(1, 1, -1);
    glColor3f(1, 0, 0); glVertex3f(1, -1, -1);

    glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
    glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
    glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
    glColor3f(1, 0, 1); glVertex3f(1, -1, 1);

    /* No more quads */
    glEnd();
}

void display2() {
    static float alpha = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glViewport(0, 0, width / 2, height);
    gluPerspective(20, ((float)width / 2) / height, 5, 15);
    drawCube(alpha);
    glPopMatrix();
    glFlush();

    glPushMatrix();
    glViewport(width / 2, 0, width / 2, height);
    gluPerspective(45, ((float)width / 2) / height, 5, 15);
    glColor3f(1, 1, 0);
    glTranslatef(0, 0, -10);
    //drawCube(alpha);
    glutWireTeapot(1);
    glPopMatrix();
    glFlush();

    alpha = alpha + 0.1;

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape2(int w, int h) {
    width = w;
    height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
