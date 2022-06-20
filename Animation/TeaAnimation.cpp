#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static bool isKey = false;
static bool ismouse = false;
static float posx = 0;
static GLfloat spin = 0;

void init() {
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
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
	glPushMatrix();
	if (isKey) {
		glTranslatef(posx, 0, 0);
	}
	if (ismouse) {
		glRotatef(spin,0,0,1);
	}
	glutWireTeacup(3);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();

}

void movIzq() {
	if (isKey) {
		posx -= 0.0005;

	}
	if (ismouse) {
		spin -= 0.05;
		if (spin<-360) {
			spin += 360;
		
		}
	}
	glutPostRedisplay();
}

void movDer() {
	if (isKey) {
		posx += 0.0005;

	}
	if (ismouse) {
		spin += 0.05;
		if (spin < -360) {
			spin += 360;

		}
	}
	glutPostRedisplay();
}

void keyboard(int key, int, int ) {
	switch (key) {
		case GLUT_KEY_LEFT:
			isKey = true;
			glutIdleFunc(movIzq);
			break;
		case GLUT_KEY_RIGHT:
			isKey = true;
			glutIdleFunc(movDer);
			break;
		default:
			break;
	}

}

void keyboardUP(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT:
		isKey = false;
		glutIdleFunc(NULL);
		break;
	case GLUT_KEY_RIGHT:
		isKey = false;
		glutIdleFunc(NULL);
		break;
	default:
		break;

	}

}

void mouse(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
				if (state==GLUT_DOWN) {
					ismouse = true;
					glutIdleFunc(movIzq);
				}
				else if (state==GLUT_UP) {
					ismouse = false;
					glutIdleFunc(NULL);
				}
			break;
		case GLUT_RIGHT_BUTTON:
				if(state == GLUT_DOWN) {
					ismouse = true;
					glutIdleFunc(movDer);
				}
				else if (state == GLUT_UP) {
					ismouse = false;
					glutIdleFunc(NULL);
				}
			break;
		default:
			break;
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Ejemplo animación");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboardUP);
	glutMouseFunc(mouse);
	


	glutMainLoop();
	return 0;
	
}
