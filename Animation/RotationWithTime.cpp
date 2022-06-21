#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLfloat angulo=0,angulo2=0,angulo3=0;
int tiempo = 5;
void init() {
    glClearColor(0, 0, 0, 0);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void reshape(GLsizei w, GLsizei h) {
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, w, h);
}

void cubo() {
    glBegin(GL_QUADS);
    //Top
    glColor3f(0.9, 0.8, 0.7);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    //Bottom
    glColor3f(1, 0.5, 0);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    //Delate
    glColor3f(0, 0.4, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    //Atras
    glColor3f(0.8, 0.2, 0.4);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    //Izq
    glColor3f(0.9, 0.8, 0.2);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    //Der
    glColor3f(1, 0.7, 0.3);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glEnd();
}

void timer(int valor) {
    glutPostRedisplay();
    glutTimerFunc(tiempo, timer,0);


}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angulo, 0, 1, 1);
    cubo();
    glPopMatrix();
    

    //nuevo cubo trasladado
    glPushMatrix();
    glTranslatef(-4,1,0);
    glScalef(0.8,0.8,0.8);
    glRotatef(angulo2, 1, 1, 1);
    cubo();
    glPopMatrix();
    //nuevo cubo trasladado
    glPushMatrix();
    glTranslatef(4, -1, 0);
    glScalef(0.8, 0.8, 0.8);
    glRotatef(angulo3, 1, 1, 1);
    cubo();
    glPopMatrix();

    glFlush();
    angulo += 0.15;
    angulo2 += 0.3;
    angulo3 += 0.5;
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(800, 680);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ejemplo animacion");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(0, timer,0);
    glutMainLoop();
    
    return 0;
}
