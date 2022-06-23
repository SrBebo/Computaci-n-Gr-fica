#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

void init() {
    
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 4, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
}

void reshape(GLsizei w, GLsizei h) {
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, w , h);
}

void mesa() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glColor3f(1.0f, 0.7f, 0.0f);
   
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glScalef(1,0.1,0.7);
    glutSolidCube(5);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();

}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ejemplo morph");
    init();
    glutDisplayFunc(mesa);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
