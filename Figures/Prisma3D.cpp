#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
}

void init3D() {
	//Llamar al color
	//glClearColor(0.9, 0.8, 0.6, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1, 4, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 5, 0, 0, 0, 0, 0, 0);
}

void prismas3D() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-1.0, 0.0, -7.0);

	glBegin(GL_TRIANGLES);

	//frente
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex3f(0.0, 1.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0, -1.0, 1.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0, -1.0, 1.0);

	//derecha
	glColor3f(0.7f, 0.5f, 0.1f);
	glVertex3f(0.0, 1.0, 0.0);
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex3f(1.0, -1.0, 1.0);
	glColor3f(4.0f, 3.0f, 1.0f);
	glVertex3f(1.0, -1.0, -1.0);

	//atras
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0, 1.0, 0.0);
	glColor3f(0.0f, 0.7f, 1.0f);
	glVertex3f(1.0, -1.0, -1.0);
	glColor3f(1.0f, 2.0f, 0.0f);
	glVertex3f(-1.0, -1.0, -1.0);

	//izquierda
	glColor3f(1, 0, 0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	glEnd();
	glutSwapBuffers();
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(648, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ejemplos 3D");
	glutDisplayFunc(prismas3D);
	glutReshapeFunc(reshape);
	init3D();
	glutMainLoop();
}
