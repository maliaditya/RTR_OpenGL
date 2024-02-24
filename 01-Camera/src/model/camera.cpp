#include "camera.h"


void Camera::update(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    // Code

  if (uMsg == WM_MOUSEMOVE) {

    xpos = LOWORD(lParam);
    ypos = HIWORD(lParam);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = FALSE;
    }

    xoffset = xpos - lastX;
    yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;


    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 90.0f)
        pitch = 90.0f;
    if (pitch < -90.0f)
        pitch = -90.0f;

    front[0] = cos(yaw) * cos(pitch);
    front[1] = sin(pitch);
    front[2] = sin(yaw) * cos(pitch);
    normalize(front);
}
   else if (uMsg == WM_KEYDOWN) {
   
   if(wParam == 'W' || wParam == 'w') {
    pos += speed * front;
   }
   if(wParam == 'S' || wParam == 's') {
    pos -= speed * front;
   }
   if(wParam == 'A' || wParam == 'a') {
    pos -= normalize(cross(front, up)) * speed;
   }
   if(wParam == 'D' || wParam == 'd') {
    pos += normalize(cross(front, up)) * speed; 
   }
   
   
   }
}


vmath::mat4  Camera::getMatrix()
{
    // code
    return vmath::lookat(pos, pos + front, up);
}
