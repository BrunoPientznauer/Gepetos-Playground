#include "globals.h"

bool  MouseContext::mouseOnRightEdge = false;
bool  MouseContext::mouseOnLeftEdge = false;
bool  MouseContext::mouseOnUpperdge = false;
bool  MouseContext::mouseOnLowerEdge = false;
bool  MouseContext::firstMouse = true;
float MouseContext::lastMouseX = 0.f;
float MouseContext::lastMouseY = 0.f;
float MouseContext::posX;
float MouseContext::posY;

void MouseContext::Update(GLFWwindow *window, double xPos, double yPos) {
  if (firstMouse) {
    lastMouseX = xPos;
    lastMouseY = yPos;
    firstMouse = false;
  }else{
    lastMouseX = posX;
    lastMouseY = posY;
  }

  posX = xPos;
  posY = yPos;

  int screenWidth;
  int screenHeight;

  glfwGetWindowSize(window, &screenWidth, &screenHeight);

  // calculates if mouse is on horizontal edge of the screen
  mouseOnRightEdge = (xPos >= (screenWidth - SCREEN_MARGIN));
  mouseOnLeftEdge = (xPos <= SCREEN_MARGIN);

  // calculates if mouse is on vertical edge of the screen
  mouseOnUpperdge = (yPos <= 0);
  mouseOnLowerEdge = (yPos > (screenHeight - SCREEN_MARGIN));
}
