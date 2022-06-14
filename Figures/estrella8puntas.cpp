#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
}

void triangulos() {
	glClearColor(0.9, 0.8, 0.6, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor4f(0.4, 0.6, 0.7, 1);
	//Triangulo 1
	glVertex2f(75, 80);
	glVertex2f(10, 0);
	glVertex2f(75, -80);

	//Triangulo 2
	glVertex2f(-75, 80);
	glVertex2f(-10, 0);
	glVertex2f(-75, -80);

	glEnd();
	glutSwapBuffers();
}

void printMatriz(glm::mat4 matriz) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%.2f\t", matriz[j][i]);
		}
		std::cout << std::endl;
	}
}

void rectangulo() {
	glClearColor(0.9, 0.8, 0.6, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(0.4, 0.6, 0.7, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRectf(-10, -10, 10, 10);

	glTranslatef(20, 30, 0);
	glLoadIdentity();
	glRotatef(45, 0, 0, 1);
	glRectf(-10, -10, 10, 10);
	glutSwapBuffers();
}

int main(int argc, char** argv) {

	glm::mat4 transform;
	transform = glm::mat4(1);
	//std::cout << "Identidad: " << std::endl;
	//printMatriz(transform);

	//std::cout << std::endl;

	transform = glm::translate(transform, glm::vec3(0.5, -0.5, 0));
	//std::cout << "Traslacion: " << std::endl;
	//printMatriz(transform);

	//std::cout << std::endl;

	transform = glm::rotate(transform, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//std::cout << "Rotacion: " << std::endl;
	//printMatriz(transform);

	//std::cout << std::endl;

	transform = glm::scale(transform, glm::vec3(5.0f, 5.0f, 0.0f));
	//std::cout << "Escala: " << std::endl;
	//printMatriz(transform);




	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(648, 480);
	glutCreateWindow("Ejemplos 2D y 3D");
	glutDisplayFunc(rectangulo);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
