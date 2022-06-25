#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

//Sol
static float rotacion_sol = 0.0;
static float radius_sol = 10.0;
static int tiempo = 5;
int a = 600, b = 600;
double rx = 0, ry = 0, rz = 0, px = 0, py = 0, pz = 0;
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void reshape(GLint w, GLint h) {
	if (h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,(GLfloat)b/(GLfloat)a,1,300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void sol() {
	//SOL
	glColor3f(1.0, 1.0, 0.0);  // --> Color Amarillo	
	//Esfera
	//glutSolidSphere(4.0, 20, 20);
	
	glutWireSphere(4.0, 20, 20);
}

void timer(int valor) {
	glutPostRedisplay();
	glutTimerFunc(tiempo, timer, 0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-10+rx,9+ry,-10+rz,px,py,pz,0,1,0);
	glPushMatrix();
	//Sol
	glPushMatrix();
	glRotatef(rotacion_sol, 0.0, 0.0, 1.0);
	sol();
	glPopMatrix();

	rotacion_sol += 0.15;
	glutSwapBuffers();
	glFlush();

}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;

	//para eje x
	case 'd':
		rx = rx + 0.2;
		break;
	case 'a':
		rx = rx - 0.2;
		break;
	case 'l':
		px = px + 0.8;
		break;
	case 'j':
		px = px - 0.2;
		break;

	//para eje y

	case 'q':
		ry = ry + 0.2;
		break;
	case 'e':
		ry = ry - 0.2;
		break;
	case 'u':
		py = py + 0.2;
		break;
	case 'o':
		py = py - 0.2;
		break;
	case 49://1
		ry = ry + 0.2;
		py = py + 0.2;
		break;
	case 50://2
		ry = ry - 0.2;
		py = py - 0.2;
		break;


	//eje z
	case 'w':
		rz = rz + 0.2;
		break;
	case 's':
		rz = rz - 0.2;
		break;
	case 'i':
		pz = pz + 0.8;
		break;
	default:
		break;
	}
	glutPostRedisplay();

}

void flechas(int key,int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		rx = rx - 0.2;
		px = px - 0.2;
		break;
	case GLUT_KEY_RIGHT:
		rx = rx + 0.2;
		px = px + 0.2;
		break;
	case GLUT_KEY_UP:
		rz = rz - 0.2;
		pz = pz - 0.2;
		break;
	case GLUT_KEY_DOWN:
		rz = rz - 0.2;
		pz = pz - 0.2;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Proyecto version 1.1");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(flechas);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}
