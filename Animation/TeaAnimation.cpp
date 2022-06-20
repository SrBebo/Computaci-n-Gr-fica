#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



void init() {
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,10,0,0,0,0,1,0);

}


void reshape(GLsizei w, GLsizei h) {
	if (h==0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
	glutWireTeacup(1);
	glutSwapBuffers();

}



int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(688, 480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Ejemplo animación");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
	
}
