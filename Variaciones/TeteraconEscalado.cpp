#include <GL/freeglut.h>

void reshape(GLint w, GLint h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	/*glColor3f(0, 0, 0);*/
	glLoadIdentity();

	glTranslatef(0.0,0.0,0.0);
	glScalef(1.0,1.0,1.0);
	gluOrtho2D(-1.5, 1.5, -1.5, 1.5);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(5, 0, 10, 0, 0, 0, 0, 1, 0);
	glRotatef(0.0,2.0,1.0,0.0);
	glRotatef(0.0,1.0,0.0,0.0);
	glutWireTeapot(1);
	glFlush();

int main(int arge, char* argv[]) {

	glutInit(&arge, argv);

	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(50, 50);
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
