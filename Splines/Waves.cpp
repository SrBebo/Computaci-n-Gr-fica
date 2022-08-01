#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

double controlPoints[45][45][3];
int refreshRate = 15;
int waveControl = 0;
GLfloat hold = 0;

void initLuces();
void initGL();
void reshape(GLsizei w, GLsizei h);
void timer(int value);
void display();
void spline();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Ejemplo");

	initGL();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	spline();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();

}

void spline() {
	int Xpos = 0;
	int Ypos = 0;

	glLoadIdentity();
	glColor4f(1.0, 0.4, 0.3, 1.0);
	glTranslatef(0.0, 0.0, -12.0);
	glScalef(0.8, 0.8, 0.8);
	glRotatef(45, 1, 0, 0);

	//glBegin(GL_LINE_STRIP);
	glBegin(GL_QUADS);

	for (Xpos = 0; Xpos < 44; Xpos++) {
		for (Ypos = 0; Ypos < 44; Ypos++) {
			glVertex3f(controlPoints[Xpos][Ypos][0], controlPoints[Xpos][Ypos][1], controlPoints[Xpos][Ypos][2]);
			glVertex3f(controlPoints[Xpos][Ypos + 1][0], controlPoints[Xpos][Ypos + 1][1], controlPoints[Xpos][Ypos + 1][2]);
			glVertex3f(controlPoints[Xpos + 1][Ypos + 1][0], controlPoints[Xpos + 1][Ypos + 1][1], controlPoints[Xpos + 1][Ypos + 1][2]);
			glVertex3f(controlPoints[Xpos + 1][Ypos][0], controlPoints[Xpos + 1][Ypos][1], controlPoints[Xpos + 1][Ypos][2]);

		}
	}

	glEnd();

	if (waveControl==2) {
		for(Ypos = 0; Ypos < 45; Ypos++){
			hold = controlPoints[0][Ypos][2];
			for (Xpos = 0; Xpos < 44; Xpos++) {
				controlPoints[Xpos][Ypos][2] = controlPoints[Xpos+1][Ypos][2];
			
			}
			controlPoints[44][Ypos][2] = hold;
		}
		waveControl = 0;
	}
	waveControl++;
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshRate, timer, 0);
}

void initLuces() {
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void reshape(GLsizei w, GLsizei h) {
	if (h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (GLfloat)w / h, 1, 40);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();

}

void initGL() {
	glClearColor(0.2, 0.25, 0.35, 1.0);
	glEnable(GL_DEPTH_TEST);
	initLuces();

	for (int x = 0; x < 45; x++) {
		for (int y = 0; y < 45; y++) {
			controlPoints[x][y][0] = double((x / 3) - 7);
			controlPoints[x][y][1] = double((y / 5) - 4);
			controlPoints[x][y][2] = double(sin((((x / 5.0f) * 40.0f) / 360.0f) * M_PI * 2.0f));
		}
	}
}
