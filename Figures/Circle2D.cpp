#include <GL/freeglut.h>
#include <math.h>

float radio = 80, calx, caly;

void reshape(GLint w, GLint h) {
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100, 100, -100, 100);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex3f(0.5f,-0.5f,0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	for (float i = 0; i < 80; i += 0.01) {
		calx = radio * cos(i);
		caly = radio * sin(i);
		glVertex2f(calx, caly);
	}
	glEnd();
	glFlush();

}
int main(int arge, char* argv[]) {

	glutInit(&arge, argv);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(20, 20);
	glutInitDisplayMode(GLUT_RGB);
	//crear la ventena
	glutCreateWindow("Objeto dimensional");
	/*glClearColor(1, 1, 30, 0);*/
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
	return 0;
}
