#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

class UserInterface {
public:
    UserInterface(GLFWwindow* window);
    ~UserInterface();
    float rotationSpeedMultiplier = 1.0f;
    void render();

private:
    GLFWwindow* window;
};

#endif
