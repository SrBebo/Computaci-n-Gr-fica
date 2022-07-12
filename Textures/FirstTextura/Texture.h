#pragma once

#ifndef FigurasGLM_TEXTURE.H /*Nombre del proyecto*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

class Texture {
private:
    GLuint id;
    int w, h, nrChannels;
public:

    Texture(const char* texturePath, GLint textureFormat) {
        if (id) {
            glDeleteTextures(1, &id);
        }
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(texturePath, &w, &h, &nrChannels, 0);
        checkImageData(data, textureFormat, w, h);
        stbi_image_free(data);
    }

    ~Texture() { glDeleteTextures(1, &id); }

    void bind(GLenum type) {
        glEnable(type);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glBindTexture(type, id);
    }

    void unbind(GLenum type) {
        glDisable(type);
        glBindTexture(type, 0);
    }

private:
    void checkImageData(unsigned char* data, GLint textureFormat, int w, int h) {
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, w, h, 0, textureFormat, GL_UNSIGNED_BYTE, data);
        }
        else {
            printf("Error al cargar la imagen\n");
        }
    }
};

#endif 
