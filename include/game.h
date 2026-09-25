#pragma once

#include "scene_renderer.h"
#include "camera_handle.h"

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

 void mouseCallback(GLFWwindow *window);
 void mouseButtonCallback(GLFWwindow *window, int button);

 private:
 Scene createScene();
};