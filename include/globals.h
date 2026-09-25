#pragma once

#include <GLFW/glfw3.h>

#define SCREEN_MARGIN 10.f


class MouseContext{
public:
  static bool  mouseOnRightEdge;
  static bool  mouseOnLeftEdge;
  static bool  mouseOnUpperdge;
  static bool  mouseOnLowerEdge;
  static bool  firstMouse;
  static float lastMouseX;
  static float lastMouseY;
  static float posX;
  static float posY;

public:
  static void Update(GLFWwindow *window, double xPos, double yPos);
};
