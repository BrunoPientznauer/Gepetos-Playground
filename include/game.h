#pragma once

#include "scene_renderer.h"
#include <GLFW/glfw3.h>

class Game {
private:
  Scene    m_scene;
  Renderer m_renderer;

  Mesh m_terrain;

public:
 Game();
 ~Game();

 void Init();
 void Update(float deltaTime);
 void Render();
 void ProcessInputs(GLFWwindow* window, float deltaTime);

 void mouseCallback(GLFWwindow *window, double xpos, double ypos);
 void mouseButtonCallback(GLFWwindow *window, int button);

 private:
 Scene createScene();
};