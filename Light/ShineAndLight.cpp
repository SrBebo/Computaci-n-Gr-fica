#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>


void init() {
    GLfloat ambiente[] = { 0, 0, 0, 1 };
    GLfloat difusa[] = { 1, 1, 1, 1 };
    GLfloat posicion[] = { 2, 3, 2,0 };
    GLfloat lmodel_ambiente[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = {0};

    glClearColor(0.1,0.1,0.1,0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
    glLightfv(GL_LIGHT0, GL_POSITION, posicion);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiente);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void display() {
    GLfloat notmat[]={0,0,0,1};
    GLfloat mat_ambiente_color[] = {1, 0.3, 0.3, 1.0};
    GLfloat mat_ambiente[] = {0.33, 0.22, 0.03, 1.0};
    GLfloat mat_difusa[] = {0.8, 0.6, 0.11, 1.0};
    GLfloat mat_specular[] = {1, 0.9, 0.8, 1.0};
    GLfloat no_brillo[] = {0};
    GLfloat bajo_brillo[] = {5};
    GLfloat alto_brillo[] = { 100 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(-3.75, 0.0, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, notmat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, notmat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_brillo);
    glutSolidSphere(1,16,16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75, 0.0, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, notmat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, bajo_brillo);
    glutSolidSphere(1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.25, 0.0, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, notmat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, alto_brillo);
    glutSolidSphere(1, 16, 16);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= (h * 2))
        glOrtho(-6, 4, -3 * ((GLfloat)(h * 2)) / (GLfloat)w, 3 * ((GLfloat)(h * 2)) / (GLfloat)w, -10, 10);
    else
        glOrtho(-5 * (GLfloat)w / ((GLfloat)h * 2), 5 * (GLfloat)w / ((GLfloat)h * 2), -3, 3, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    /* Use single color buffer instead of a depth buffer */
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    /* Windows dimensions - width and height */
    glutInitWindowSize(450, 450);
    /* Location of window - screen coordinates */
    glutInitWindowPosition(100, 100);
    /* Sets the window object name */
    glutCreateWindow("Ejemplo iluminación");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
