#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameWindow{
private:
 GLFWwindow *window;

public:

 GameWindow(int width, int height, char* title);
 ~GameWindow();

private:
 static void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
 static void mouseCallback(GLFWwindow *window, double xpos, double ypos);
 static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

};