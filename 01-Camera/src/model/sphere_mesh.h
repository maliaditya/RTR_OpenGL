#pragma once

#include "buffer.h"
#include <GL/glew.h> // This Must Be Before Including <GL/gl.h>
#include <GL/gl.h>
#include  "../../include/Sphere.h"
#include  "../../include/global.h"

class SphereMesh {
public:
    SphereMesh();
    ~SphereMesh();

    void init();
    void uninitialize();

    float sphere_vertices[1146];
    float sphere_normals[1146];
    float sphere_textures[764];
    unsigned short sphere_elements[2280];

    GLuint VAO;
    GLuint EBO;
    GLuint VBO_Position;
    GLuint VBO_Texcoord;
    GLuint VBO_Normal;

    GLsizei gNumVertices;
    GLsizei gNumElements;

    Buffer buffer;
};
