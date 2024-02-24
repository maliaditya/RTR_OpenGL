#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include <GL/glew.h>
#include <GL/gl.h>

#include "../model/renderable_entity.h"
#include "../../include/window_util.h"
#include "../model/sphere_mesh.h"
#include "../model/shader.h"
#include "../model/camera.h"
#include "stack.hpp"

#define WINWIDTH 800
#define WINHEIGHT 600





class Renderer {
private:
    Logger logger;
    
public:
    Renderer():logger("renderer.log"){};
    SphereMesh s;
    Camera camera;
    std::map<std::string, RenderableEntity> entityMap;
    TransformationStack stack;

    BOOL gbActiveWindow = FALSE;
    HWND ghwnd = NULL;
    HDC ghdc = NULL;
    HGLRC ghrc = NULL;
    BOOL gbFullscreen = FALSE;
 
    mat4 perspectiveProjectionMatrix;

    GLuint shaderProgramObject;
    int day = 0;
    int year = 0;
    int moonx = 0;

    int initialize();
    void render();
    void update();
    int deviceSetup();
    void defaultSettings();
};