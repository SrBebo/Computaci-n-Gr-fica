#include <iostream>
#include <GL/freeglut.h>

GLfloat rotAngle = 0.0f;
int refreshRate = 30;


void init() {
    GLfloat ambiente[] = { 0,0,0,1 };
    GLfloat difusa[] = { 1,1,1,1 };
    GLfloat specular[] = { 1,1,1,1 };
    GLfloat posicion[] = { 1,1,1,0 };
    GLfloat lmodel_ambiente[] = { 0.4,0.4,0.4,1.0 };
    GLfloat local_view[] = { 0 };

    glClearColor(0.2, 0.25, 0.34, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicion);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiente);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}



void reshape(int w, int h) {
    /* Compute aspect ratio of the new window */
    if (h == 0) {
        h = 1;
    }

    GLfloat aspect = (GLfloat)w / (GLfloat)h;

    /* Sets the viewport to cover the new window*/
    glViewport(0, 0, w, h);

    /* Sets the aspect ratio of the clipping volume to match the viewport*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Enable perspective projection with fovy, aspect, zNear and zFar */
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void display() {
    GLfloat notmat[] = { 0,0,0,1 };
    GLfloat mat_ambiente[] = { 0.33,0.22,0.03,1.0 };
    GLfloat mat_difusa[] = { 0.8,0.6,0.11,1.0 };
    GLfloat mat_specular[] = { 1.0,0.9,0.2,1.0 };
    GLfloat no_brillo[] = { 0.0 };
    GLfloat bajo_brillo[] = { 5.0 };
    GLfloat alto_brillo[] = { 30.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(-2, 0, -6);
    glRotatef(rotAngle, 0, 1, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, notmat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, notmat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_brillo);
    glutSolidTeapot(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -6);
    glRotatef(rotAngle, 0, 1, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, notmat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, notmat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, alto_brillo);
    glutSolidTeapot(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0, -6);
    glRotatef(rotAngle, 0, 1, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, bajo_brillo);
    glutSolidTeapot(0.5);
    glPopMatrix();

    glutSwapBuffers();
    rotAngle += 1;
}

void myTimer(int value) {
    glutPostRedisplay();                                        // activates displayL as a new request
    glutTimerFunc(refreshRate, myTimer, 0);    // calls the next timer
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    //glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    //glutInitWindowSize (450, 640);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Ejemplo iluminación");
    
    init();
  
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(0, myTimer, 0);
    glutMainLoop();
    return 0;
}
