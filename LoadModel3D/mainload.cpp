#include <math.h>
#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

//#include <time.h>
#include <iostream>

#include <fstream>
#include <map>
#include <vector>

#include <Includes/loadpng.h>
#include <Includes/process_image.h>
#include <Includes/gl_texture.h>


/* GLOBAL VARIABLES */
/* ------------------------------------------------------- */

/* Screen settings */
const unsigned int SCR_WIDTH = 720;
const unsigned int SCR_HEIGHT = 720;

/* Screen center */
static int centerX = SCR_WIDTH / 2;
static int centerY = SCR_HEIGHT / 2;

#define INTERVAL 15

/* CLASSES*/
/* ------------------------------------------------------- */

/* Creates the loaded model */
class Model
{
private:
    static int countChar(std::string& str, char ch) {
        int c = 0;
        int length = str.length() - 1;
        for (int i = 0; i < length; i++) {
            if (str[i] == ch)
                c++;
        }
        return c;
    }

    static bool isDoubleSlash(std::string& str) {
        int length = str.length() - 2;
        for (int i = 0; i < length; i++) {
            if (str[i] == '/' && str[i + 1] == '/')
                return true;
        }
        return false;
    }

    /* Subclass that loads the model materials */
    class Material {
    public:
        /* Model materials attributes */
        float* ambient;
        float* diffuse;
        float* specular;
        GLuint texture;

        Material(float* ambient, float* diffuse, float* specular) {
            this->ambient = ambient;
            this->diffuse = diffuse;
            this->specular = specular;
            this->texture = 0;
        }
    };

    /* Subclass that identifies the model faces */
    class Face {
    public:
        int edge;
        int* vertices;
        int* texcoords;
        int normal;

        Face(int edge, int* vertices, int* texcoords, int normal = -1) {
            this->edge = edge;
            this->vertices = vertices;
            this->texcoords = texcoords;
            this->normal = normal;
        }
    };

    /* Local model attributes */
    std::string prefix;
    std::vector<Material> materials;
    std::map<std::string, int> map_material;

    std::vector<float*> vertices;
    std::vector<float*> texcoords;
    std::vector<float*> normals;
    std::vector<Face> faces;

    GLuint list;

    /* Method that loads the model material */
    void loadMaterial(const char* filename) {
        /* Local attributes */
        Material* m = NULL;
        int count_material = 0;
        char str[40];
        std::string material;
        float* a = 0;
        float* d = 0;
        float* s = 0;

        /* File lines */
        std::string line;
        std::vector<std::string> lines;
        std::ifstream in(filename);

        /* Couldn't load material data */
        if (!in.is_open()) {
            std::cout << "Cannot load material " << filename << std::endl;
            return;
        }

        /* Gets all the file lines */
        while (!in.eof()) {
            std::getline(in, line);
            lines.push_back(line);
        }
        in.close();

        /* Set the attributes according to MTL file */
        for (std::string& line : lines) {
            if (line[0] == 'n' && line[1] == 'e') {
                sscanf(line.c_str(), "newmtl %s", str);
                material = str;
                map_material[material] = count_material;
                count_material++;
                a = new float[4]{ 0.2f, 0.2f, 0.2f, 1.0f };
                d = new float[4]{ 0.8f, 0.8f, 0.8f, 1.0f };
                s = new float[4]{ 0.0f, 0.0f, 0.0f, 1.0f };
                materials.push_back(Material(a, d, s));
                m = &materials[materials.size() - 1];
            } else if (line[0] == 'K') {
                switch (line[1]) {
                    case 'a':
                        sscanf(line.c_str(), "Ka %f %f %f", &a[0], &a[1], &a[2]);
                        break;
                    case 'd':
                        sscanf(line.c_str(), "Kd %f %f %f", &d[0], &d[1], &d[2]);
                        break;
                    case 's':
                        sscanf(line.c_str(), "Ks %f %f %f", &s[0], &s[1], &s[2]);
                        break;
                }
            } else if (line[0] == 'm' && line[1] == 'a') {
                /* Texture image */
                Image img;
                std::string file = prefix + str;

                /* Reads and loads the texture */
                sscanf(line.c_str(), "map_Kd %s", str);

                /* Swaps the loaded texture */
                Load_Texture_Swap(&img, file.c_str());

                /* Binds the texture */
                glGenTextures(1, &(m->texture));
                glBindTexture(GL_TEXTURE_2D, m->texture);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.img);
                glBindTexture(GL_TEXTURE_2D, 0);

                /* Free resources */
                Delete_Image(&img);
            }
        }
    }

    /* Sets model faces */
    /* ------------------------------------------------------- */
    void addFace3v(std::string& line) {
        /* Face vertices */
        int v0;
        int v1;
        int v2;

        /* Saves the vertices data */
        sscanf(line.c_str(), "f %d %d %d", &v0, &v1, &v2);
        int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
        faces.push_back(Face(3, v, NULL));
    }

    void addFace3vt(std::string& line) {
        /* Face vertices and texture vertices */
        int v0, v1, v2, t0, t1, t2;

        /* Saves the vertices data */
        sscanf(line.c_str(), "f %d/%d %d/%d %d/%d", &v0, &t0, &v1, &t1, &v2, &t2);
        int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
        int* t = new int[3]{ t0 - 1, t1 - 1, t2 - 1 };
        faces.push_back(Face(3, v, t));
    }

    void addFace3vn(std::string& line) {
        /* Normal face vertices */
        int v0, v1, v2, n;

        /* Saves the vertices data */
        sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &v0, &n, &v1, &n, &v2, &n);
        int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
        faces.push_back(Face(3, v, NULL, n - 1));
    }

    void addFace3vtn(std::string& line) {
        /* Vertices */
        int v0, v1, v2, t0, t1, t2, n;

        /* Saves the vertices data */
        sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
        int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
        int* t = new int[3]{ t0 - 1, t1 - 1, t2 - 1 };
        faces.push_back(Face(3, v, t, n - 1));
    }

    void addFace4v(std::string& line) {
        /* Model face vertices */
        int v0, v1, v2, v3;

        /* Saves the vertices data */
        sscanf(line.c_str(), "f %d %d %d %d", &v0, &v1, &v2, &v3);
        int* v = new int[4]{ v0 - 1, v1 - 1, v2 - 1, v3 - 1 };
        faces.push_back(Face(4, v, NULL));
    }

    void addFace4vt(std::string& line) {
        /* Model face texture vertices */
        int v0, v1, v2, v3, t0, t1, t2, t3;

        /* Saves the vertices data */
        sscanf(line.c_str(), "f %d/%d %d/%d %d/%d %d/%d", &v0, &t0, &v1, &t1, &v2, &t2, &v3, &t3);
        int* v = new int[4]{ v0 - 1, v1 - 1, v2 - 1, v3 - 1 };
        int* t = new int[4]{ t0 - 1, t1 - 1, t2 - 1, t3 - 1 };
        faces.push_back(Face(4, v, t));
    }

    void addFace4vn(std::string& line) {
        /* Model face normal vertices */
        int v0, v1, v2, v3, n;

        /* Saves the vertices data */
        sscanf(line.c_str(), "f %d//%d %d//%d %d//%d %d//%d", &v0, &n, &v1, &n, &v2, &n, &v3, &n);
        int* v = new int[4]{ v0 - 1, v1 - 1, v2 - 1, v3 - 1 };
        faces.push_back(Face(4, v, NULL, n - 1));
    }

    void addFace4vtn(std::string& line) {
        /* Normal texture vertices */
        int v0, v1, v2, v3, t0, t1, t2, t3, n;

        /* Saves the vertices data */
        sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n, &v3,
               &t3, &n);
        int* v = new int[4]{ v0 - 1, v1 - 1, v2 - 1, v3 - 1 };
        int* t = new int[4]{ t0 - 1, t1 - 1, t2 - 1, t3 - 1 };
        faces.push_back(Face(4, v, t, n - 1));
    }

public:
    /* Model position */
    float posX, posY, posZ;

    /* Loads the model */
    void load(const char* filename) {
        std::string tmp = filename;
        prefix = "";
        int n = tmp.find_last_of('/') + 1;
        if (n > 0)
            prefix = tmp.substr(0, n);

        std::string line;
        std::vector<std::string> lines;
        std::ifstream in(filename);

        /* Is unable to read data */
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
        char str[40];

        posX = posY = 0.0f;

        float sum_x = 0.0f, sum_y = 0.0f, sum_z = 0.0f;

        /* Iterates with each mtl line */
        for (std::string& line : lines) {
            if (line[0] == 'v') {
                if (line[1] == ' ') {
                    sscanf(line.c_str(), "v %f %f %f", &a, &b, &c);
                    if (a > 0.0f)
                        sum_x += a;
                    else
                        sum_x -= a;
                    if (b > 0.0f)
                        sum_y += b;
                    else
                        sum_y -= b;
                    if (c > 0.0f)
                        sum_z += c;
                    else
                        sum_z -= c;
                    posX += a;
                    posY += b;
                    vertices.push_back(new float[3]{ a, b, c });
                }
                else if (line[1] == 't') {
                    sscanf(line.c_str(), "vt %f %f", &a, &b);
                    texcoords.push_back(new float[2]{ a, b });
                }
                else {
                    sscanf(line.c_str(), "vn %f %f %f", &a, &b, &c);
                    normals.push_back(new float[3]{ a, b, c });
                }
            }
            else if (line[0] == 'f') {
                /* Adds each face */
                int edge = countChar(line, ' ');
                int count_slash = countChar(line, '/');
                if (count_slash == 0) {
                    if (edge == 3)
                        addFace3v(line);
                    else
                        addFace4v(line);
                }
                else if (count_slash == edge) {
                    if (edge == 3)
                        addFace3vt(line);
                    else
                        addFace4vt(line);
                }
                else if (count_slash == edge * 2) {
                    if (isDoubleSlash(line)) {
                        if (edge == 3)
                            addFace3vn(line);
                        else
                            addFace4vn(line);
                    }
                    else {
                        if (edge == 3)
                            addFace3vtn(line);
                        else
                            addFace4vtn(line);
                    }
                }
            } else if (line[0] == 'm' && line[1] == 't') {
                sscanf(line.c_str(), "mtllib %s", &str);
                std::string file = prefix + str;
                loadMaterial(file.c_str());
            } else if (line[0] == 'u' && line[1] == 's') {
                /* Material mapping */
                sscanf(line.c_str(), "usemtl %s", &str);
                std::string material = str;
                if (map_material.find(material) != map_material.end()) {
                    faces.push_back(Face(-1, NULL, NULL, map_material[material]));
                }
            }
        }

        bool hasTextureCoordinates = false;

        list = glGenLists(1);
        glNewList(list, GL_COMPILE);
        for (Face& face : faces) {
            if (face.edge == -1) {
                hasTextureCoordinates = false;
                glLightfv(GL_LIGHT0, GL_AMBIENT, materials[face.normal].ambient);
                glLightfv(GL_LIGHT0, GL_DIFFUSE, materials[face.normal].diffuse);
                glLightfv(GL_LIGHT0, GL_SPECULAR, materials[face.normal].specular);
                if (materials[face.normal].texture != 0) {
                    hasTextureCoordinates = true;
                    glBindTexture(GL_TEXTURE_2D, materials[face.normal].texture);
                }
                continue;
            }
            if (face.normal != -1)
                glNormal3fv(normals[face.normal]);
            else
                glDisable(GL_LIGHTING);
            if (hasTextureCoordinates) {
                glBegin(GL_POLYGON);
                for (int i = 0; i < face.edge; i++) {
                    glTexCoord2fv(texcoords[face.texcoords[i]]);
                    glVertex3fv(vertices[face.vertices[i]]);
                }
                glEnd();
            }
            else {
                glBegin(GL_POLYGON);
                for (int i = 0; i < face.edge; i++)
                    glVertex3fv(vertices[face.vertices[i]]);
                glEnd();
            }
            if (face.normal == -1)
                glEnable(GL_LIGHTING);
        }
        glEndList();

        /* Sets the model path on screen */
        std::cout << "Model: " << filename << std::endl;

        sum_x /= vertices.size();
        sum_y /= vertices.size();
        sum_z /= vertices.size();
        posX /= vertices.size();
        posX = -posX;
        posY /= vertices.size();
        posY = -posY;
        posZ = -sqrt(sum_x * sum_x + sum_y * sum_y + sum_z * sum_z) * 15;

        /* Free material resources */
        for (Material& material : materials) {
            delete material.ambient;
            delete material.diffuse;
            delete material.specular;
        }
        materials.clear();
        map_material.clear();

        /* Free vertex resources */
        for (float* f : vertices)
            delete f;
        vertices.clear();
        for (float* f : texcoords)
            delete f;
        texcoords.clear();
        for (float* f : normals)
            delete f;
        normals.clear();
        faces.clear();
    }

    void draw() { glCallList(list); }
};

/* Model attributes */
std::string modelName = "stone_pillar.obj";

GLfloat light_pos[] = { -10.0f, 10.0f, 100.00f, 1.0f };

float posX, posY, posZ;
float angleX = 30.0f, angleY = 0.0f;

int oldX = 0, oldY = 0;
int currentScroll = 5;
float zoomPerScroll;

bool mouseIsDown = false;
bool isUpdated = false;

Model model;

void init() {
    /* Enables lighting*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0, 1.0, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);

    /* Alpha is enabled */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Enables texture loading */
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);

    /* Enables depth testing */
    glEnable(GL_DEPTH_TEST);

    /* Configures modal loading */
    model.load(modelName.c_str());

    posX = model.posX;
    posY = model.posY;
    posZ = model.posZ - 1.0f;

    zoomPerScroll = -model.posZ / 10.0f;
}

/* Display callback */
void display() {
    /* Depth is activated */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Loads all model transformations */
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    model.draw();
    glPopMatrix();

    /* Swaps between front and back buffers */
    glutSwapBuffers();
}

/* Sets the timer for render loop */
void timer(int value) {
    if (isUpdated) {
        isUpdated = false;
        glutPostRedisplay();
    }
    glutTimerFunc(INTERVAL, timer, 0);
}

/* Sets the mouse callback function */
void mouse(int button, int state, int x, int y) {
    /* Updates the mouse state */
    isUpdated = true;

    /* Mouse buttons are down */
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            oldX = x;
            oldY = y;
            mouseIsDown = true;
        }
        else
            mouseIsDown = false;
    }
    else if (state == GLUT_UP) {
        switch (button) {
            case 3:
                if (currentScroll > 0) {
                    currentScroll--;
                    posZ += zoomPerScroll;
                }
                break;
            case 4:
                if (currentScroll < 15) {
                    currentScroll++;
                    posZ -= zoomPerScroll;
                }
                break;
        }
    }
}

/* Mouse motion callback */
void motion(int x, int y) {
    if (mouseIsDown) {
        /* Mouse state attributes */
        isUpdated = true;
        angleY += (x - oldX);
        oldX = x;

        /* Updates the Y axis angle */
        if (angleY > 360.0f) {
            angleY -= 360.0f;
        } else if (angleY < 0.0f) {
            angleY += 360.0f;
        }

        /* Updates the position */
        angleX += (y - oldY);
        oldY = y;

        /* Updates the X axis angle */
        if (angleX > 90.0f) {
            angleX = 90.0f;
        } else if (angleX < -90.0f) {
            angleX = -90.0f;
        }

    }
}

/* MAIN */
/* ------------------------------------------------------- */
int main(int argc, char** argv) {
    /* Settings */
    /* ------------------------------------------------------- */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
//    glEnable(GL_MULTISAMPLE);
//    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
//    glutSetOption(GLUT_MULTISAMPLE, 8);

    /* Window */
    /* ------------------------------------------------------- */
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);                      // window dimensions - width and height
    glutInitWindowPosition(100, 100);                               // location of window - screen coordinates
    glutCreateWindow("COMPUTER GRAPHICS - GR1COM");                 // sets the window object name

    /* Rendering */
    /* ------------------------------------------------------- */
    init();

    /* Display */
    /* ------------------------------------------------------- */
    glutDisplayFunc(display);                                       // redraws the window

    /* Mouse */
    /* ------------------------------------------------------- */
    glutSetCursor(GLUT_CURSOR_NONE);                                // hides the cursor
    glutWarpPointer(centerX, centerY);                              // warps the mouse pointer to the screen center
    glutMouseFunc(mouse);                                           // sets the mouse callback for the current window
    glutMotionFunc(motion);                                         // sets the motion callback for the current window

    /* Render loop */
    /* ------------------------------------------------------- */
    glutTimerFunc(0, timer, 0);                                     // calls the timer
    glutMainLoop();                                                 // The program closes when user closes the window

    return 0;
}
