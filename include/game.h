#pragma once

#include "globals.h"
#include "scene_renderer.h"
#include "camera_handle.h"
#include <GLFW/glfw3.h>

class Game {
private:
  Scene    m_scene;
  Renderer m_renderer;
  FreeCameraHandle m_cameraHandle;

public:
 Game();
 ~Game();

 void Init();
 void Update();
 void Render();
 void ProcessInputs(GLFWwindow* window);

 void mouseCallback(GLFWwindow *window, double xpos, double ypos, MouseContext *mouseContex);
 void mouseButtonCallback(GLFWwindow *window, int button);

 private:
 Scene createScene();
};