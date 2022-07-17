// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <time.h>
#include <vector>

#include <GL/freeglut.h>

#define WIDTH 600
#define	HEIGHT 600


class Model {
	private:
		class Face {
			public:
				int edge;
				int *vertices;
				int* texcoords;
				int normal;

				Face(int edge, int *vertices, int *texcoords, int normal=-1) {
					this->edge = edge;
					this->vertices = vertices;
					this->texcoords = texcoords;
					this->normal = normal;

				}
		};

		std::vector <float *>vertices;
		std::vector <float *>texcoords;
		std::vector <float *>normals;
		std::vector <Face>faces;
		GLuint list;
	public:
		void load(const char *filename) {
			std::string line;
			std::vector<std::string>lines;
			
			std::ifstream in(filename);
			if (!in.is_open()) {
				printf("Cannot load model %s\n", filename);
				return;
			}
			while (!in.eof()) {
				std::getline(in, line);
				lines.push_back(line);
			}
			in.close();

			float a, b, c;
			for (std::string &line : lines) {
				if (line[0]=='v') {
					if (line[1]=' ') {
						sscanf(line.c_str(), "v %f %f %f", &a, &b, &c);
						vertices.push_back(new float[3]{a,b,c});

					}else if (line[1]=='t') {
						sscanf(line.c_str(), "vt %f %f", &a, &b);
						texcoords.push_back(new float[2] {a,b});
					}
					else {
						sscanf(line.c_str(), "cn %f %f %f", &a, &b, &c);
						normals.push_back(new float[3] {a,b,c});
					
					}
				}
				else if (line[0]=='f') {
					int v0, v1, v2, t0, t1, t2, n;
					sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
					int *v = new int[3]{v0-1, v1-1, v2-1};
					faces.push_back(Face(3, v, NULL, n-1));
				}
			}

			list = glGenLists(1);
			glNewList(list, GL_COMPILE);
			for (Face &face:faces) {
				if (face.normal !=-1){
					glNormal3fv(normals[face.normal]);
				}
				else {
					glNormal3fv();
				
	
				}

			}


		}
};
void init() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[] = { -1.0f, 10.0f, 100.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, 1.0, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GLUT_MULTISAMPLE);
	glHint(GLUT_MULTISAMPLE, GL_NICEST);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	int POS_X = (glutGet(GLUT_SCREEN_WIDTH)-WIDTH)>>1;
	int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
	glutInitWindowPosition(POS_X, POS_Y);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Load Model");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0; 

}
