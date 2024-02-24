#include "renderable_entity.h"

RenderableEntity::RenderableEntity() {
    // Initialize variables with default values
}

RenderableEntity::RenderableEntity(GLuint _program, GLuint _vao, GLuint _vbo, GLuint _ebo, int _numElements)
    : program(_program), vao(_vao), vbo(_vbo), ebo(_ebo), numElements(_numElements) {
    modelMatrix = vmath::mat4::identity();
    viewMatrix = vmath::mat4::identity();
    projectionMatrix = vmath::mat4::identity();
}

RenderableEntity::~RenderableEntity() {
    // Cleanup resources if necessary
}

vmath::mat4 RenderableEntity::setModelMatrix(vmath::mat4 model) {
    modelMatrix = model;
    return modelMatrix;
}

void RenderableEntity::setViewMatrix(vmath::mat4 view) {
    viewMatrix = view;
}

void RenderableEntity::setProjectionMatrix(vmath::mat4 projection) {
    projectionMatrix = projection;
}

void RenderableEntity::translate(vmath::vec3 translation) {
    modelMatrix = modelMatrix * vmath::translate(translation);
}

void RenderableEntity::scale(GLfloat scale) {
    modelMatrix = modelMatrix * vmath::scale(scale, scale, scale);
}

void RenderableEntity::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    modelMatrix = modelMatrix * vmath::rotate(angle, x, y, z);
}

void RenderableEntity::setColor(GLfloat r, GLfloat g, GLfloat b) {
    glVertexAttrib3f(ASM_ATTRIBUTE_COLOR, r, g, b);
}

void RenderableEntity::setPolygonMode(GLenum mode) {
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

vmath::mat4 RenderableEntity::getModelMatrix() {
    return modelMatrix * viewMatrix;
}

GLuint RenderableEntity::get(char* uniform) {
    return glGetUniformLocation(program, uniform);
}

void RenderableEntity::render() {
    glUseProgram(program);

    glUniformMatrix4fv(get("u_modelMatrix"), 1, GL_FALSE, modelMatrix);
    glUniformMatrix4fv(get("u_viewMatrix"), 1, GL_FALSE, viewMatrix);
    glUniformMatrix4fv(get("u_projectionMatrix"), 1, GL_FALSE, projectionMatrix);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}
