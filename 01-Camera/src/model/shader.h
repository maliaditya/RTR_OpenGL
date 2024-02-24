#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
#include "../../include/global.h"
#include "../../include/logger.hpp"


class Shader {
private:
    GLuint shaderProgramObject;
    const char* pVSFileName = "shaders\\shader.vert";
    const char* pFSFileName = "shaders\\shader.frag";
	FILE* file;
    Logger logger;

public:
    Shader() : logger("shader.log") {
        shaderProgramObject = glCreateProgram();
    }

    ~Shader();

    void initialize();
    void loadShadersAndCreateProgram();
    GLuint getObject();
    void bindAttributesAndLink();
    char* readShader(const char* fileName);
    void unitializeShader();
    void createAndCompileShader(const GLchar* shaderString, GLenum shaderType);
    void shaderObjectErrorChecking();
    void getAllUniformLocations(const std::string& filename);
};
