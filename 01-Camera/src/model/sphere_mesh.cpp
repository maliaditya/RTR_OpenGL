#include "sphere_mesh.h"

SphereMesh::SphereMesh() {
    getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
    gNumVertices = getNumberOfSphereVertices();
    gNumElements = getNumberOfSphereElements();
}

SphereMesh::~SphereMesh() {
    uninitialize();
}

void SphereMesh::init() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    buffer.createBuffer(VBO_Position, GL_ARRAY_BUFFER, sphere_vertices, sizeof(sphere_vertices), GL_STATIC_DRAW, ASM_ATTRIBUTE_POSITION, 3);
    buffer.createBuffer(VBO_Normal, GL_ARRAY_BUFFER, sphere_normals, sizeof(sphere_normals), GL_STATIC_DRAW, ASM_ATTRIBUTE_NORMAL, 3);
    buffer.createBuffer(EBO, GL_ELEMENT_ARRAY_BUFFER, sphere_elements, sizeof(sphere_elements), GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}

void SphereMesh::uninitialize() {
    if (VBO_Position) {
        glDeleteBuffers(1, &VBO_Position);
        VBO_Position = 0;
    }
    if (VBO_Texcoord) {
        glDeleteBuffers(1, &VBO_Texcoord);
        VBO_Texcoord = 0;
    }
    if (VBO_Normal) {
        glDeleteBuffers(1, &VBO_Normal);
        VBO_Normal = 0;
    }
    if (EBO) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
}
