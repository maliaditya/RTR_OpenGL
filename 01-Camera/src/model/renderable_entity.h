#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <fstream>
#include "../../include/vmath.h"
#include  "../../include/global.h"


class RenderableEntity {

public:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    int numElements;
    vmath::mat4 modelMatrix;
    vmath::mat4 projectionMatrix;
    vmath::mat4 viewMatrix;
    GLuint program;
    RenderableEntity();
    RenderableEntity(GLuint _program, GLuint _vao, GLuint _vbo, GLuint _ebo, int _numElements);
    ~RenderableEntity();

    vmath::mat4 setModelMatrix(vmath::mat4 model);
    void setViewMatrix(vmath::mat4 view);
    void setProjectionMatrix(vmath::mat4 projection);
    void translate(vmath::vec3 translation);
    void scale(GLfloat scale);
    void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    void setColor(GLfloat r, GLfloat g, GLfloat b);
    void setPolygonMode(GLenum mode);
    vmath::mat4 getModelMatrix();
    GLuint get(char* uniform);
    void render();
    
};
