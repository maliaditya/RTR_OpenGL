#pragma once
#include "../../include/vmath.h"
#include <Windows.h>

using namespace vmath;

class Camera {
    
    // code
    public:
        // function declaration
        void update(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        vmath::mat4 getMatrix();

    private:
        // mouse variable declaration
        double xpos;
        double ypos;
        float xoffset;
        float yoffset;

        // mouse sensitivity
        float sensitivity = 0.001f;

        // camera speed with keyboard
        const float speed = 0.05f;

        // camera initial positon
        vec3 pos = vec3(0.0f, 0.0f, 3.0f);
        vec3 front = vec3(0.0f, 0.0f, -1.0f);
        vec3 up = vec3(0.0f, 1.0f, 0.0f);

        // Initial Mouse postion
        float lastX = 400, lastY = 300, yaw = -90.0f, pitch;
        bool firstMouse = true;
    
    };
