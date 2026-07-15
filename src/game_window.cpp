#include "game_window.h"
#include <iostream>

GameWindow::GameWindow(int width, int height, char* title){
  // initialize glfw context and set hints
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  // creates window
  this->window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }

  // set callbacks
  glfwMakeContextCurrent(this->window);
  glfwSetFramebufferSizeCallback(this->window, this->frameBufferSizeCallback);
  glfwSetCursorPosCallback(this->window, this->mouseCallback);
  glfwSetMouseButtonCallback(this->window, this->mouseButtonCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glfwShowWindow(window);
  glfwMaximizeWindow(window);
}

GameWindow::~GameWindow() {
    glfwTerminate();
}

void GameWindow::frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void GameWindow::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    
}

void GameWindow::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

}
