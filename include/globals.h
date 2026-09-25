#pragma once

struct MouseContext{
  bool mouseOnRightEdge = false;
  bool mouseOnLeftEdge = false;
  bool mouseOnUpperdge = false;
  bool mouseOnLowerEdge = false;
  bool firstMouse = true;
  float lastMouseX = 0.f;
  float lastMouseY = 0.f;
};