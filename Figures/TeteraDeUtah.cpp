#include <GL/freeglut.h>

void reshape(GLint w, GLint h) {
	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	/*glColor3f(0, 0, 0);*/
	glLoadIdentity();

	gluOrtho2D(-1.5, 1.5, -1.5, 1.5);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	/*glutSolidTeapot(1);*/
	glutWireTeapot(1);
	glFlush();
}

int main(int arge, char* argv[]) {

	glutInit(&arge, argv);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(20, 20);
	//depediendo de los colores
	glutInitDisplayMode(GLUT_RGB);
	//crear la ventena
	glutCreateWindow("Objeto dimensional");
	/*glClearColor(1, 1, 30, 0);*/

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}
