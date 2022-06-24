/*fdef _APPLE_
#include <GL/freeglut.h>
#else
#include <math.h>
#endif*/
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLfloat movY = 0, movX = 0, rotar = 0, tam = 0.2, escX = 0.3, escY = 0.3, escZ = 0.1;

void principal() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(movX,movY,0.0);
    glRotatef(rotar,0.1,0.1,0.0);
    glScalef(escX, escY, escZ);
    glPushMatrix();
    glutWireSphere(tam,50,50);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void movimiento(int keys, int x, int y) {
    switch (keys){
    case GLUT_KEY_RIGHT:
        movX+= 0.1;
        break;
    case GLUT_KEY_LEFT:
        movX -= 0.1;
        break;
    case GLUT_KEY_UP:
        movY += 0.1;
        break;
    case GLUT_KEY_DOWN:
        movY -= 0.1;
        break;
    }
    glutPostRedisplay();
}
/*void aumentar(char pres) {
    switch (pres){
    case 'a':
        rotar -= 4.1;
        break;
    case 's':
        rotar += 4.1;
        break;
    case 'j':
        tam += 0.3;
        break;
    case 'k':
        tam -= 0.3;
        break;
    case 'u':
        escX+= 0.1;
        break;
    case 'i':
        escY += 0.1;
        break;
    case 'o':
        escZ += 0.1;
        break;
    }
    glutPostRedisplay();
}
*/




int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(450, 150);
    glutCreateWindow("Ejemplo animacion");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(principal);
    glutSpecialFunc(movimiento);
    //glutKeyboardFunc(aumentar);


    glutMainLoop();

    return 0;

}
