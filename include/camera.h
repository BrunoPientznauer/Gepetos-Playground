#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <game_object.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define SCREEN_MARGIN 10.f

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;

class Camera : public GameObject
{
private:
  bool m_mouseOnRightEdge = false;
  bool m_mouseOnLeftEdge = false;
  bool m_mouseOnUpperdge = false;
  bool m_mouseOnLowerEdge = false;
  bool m_firstMouse = true;
  bool m_canRotate = false;

  float m_lastMouseX = 0.f;
  float m_lastMouseY = 0.f;

public:
  /* DATA */
  float fov;
  float yaw;
  float pitch;
  float aspectRatio;

  /* Camera vectors */
  glm::vec3 front;
  glm::vec3 right;
  glm::vec3 up;
  glm::vec3 worldUp;

  float moveSpeed = 1.0f;
  float panSpeed = 1.0f;

  Camera(glm::vec3 position, float aspectRatio, float fov = 45.f,
         float yaw = YAW, float pitch = PITCH,
         glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 GetViewMatrix();

  glm::mat4 GetProjectionMatrix();

  void ProccessMouseMovement(GLFWwindow *window, double xpos, double ypos);

  void ProcessCameraRotation(float xoffset, float yoffset, GLboolean constrainPitch = true);

  void OnKeyboardDown(GLFWwindow *window, float deltaTime);

  void OnMouseButtonDown(GLFWwindow *window, int button);

  void Update(float deltaTime);

private:
  void updateCameraVectors();
};



#endif