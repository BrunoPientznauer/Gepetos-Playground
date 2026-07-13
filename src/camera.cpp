#include "camera.h"

Camera::Camera(glm::vec3 position, float fov, float yaw, float pitch, glm::vec3 worldUp): GameObject(position), fov(fov) {
  this->worldUp = worldUp;
  this->yaw = yaw;
  this->pitch = pitch;
  updateCameraVectors();
}

void Camera::ProccessMouseMovement(GLFWwindow *window, double xpos,double ypos) {
  if (firstMouse) {
    lastMouseX = xpos;
    lastMouseY = ypos;
    firstMouse = false;
  }

  int screenWidth;
  int screenHeight;

  glfwGetWindowSize(window, &screenWidth, &screenHeight);

  float xOffset = xpos - lastMouseX;
  float yOffset = lastMouseY - ypos;

  lastMouseX = xpos;
  lastMouseY = ypos;

  mouseOnRightEdge = (xpos >= (screenWidth - SCREEN_MARGIN));
  mouseOnLeftEdge = (xpos <= SCREEN_MARGIN);

  ProcessCameraRotation(xOffset, yOffset);
}

void Camera::Update(float deltaTime) {
  if (mouseOnRightEdge) {
    ProcessCameraRotation(1.f, 0.f);
  } else if (mouseOnLeftEdge) {
    ProcessCameraRotation(-1.f, 0.f);
  }

  if (mouseOnUpperdge) {
    ProcessCameraRotation(0.f, -1.f);
  } else if (mouseOnLowerEdge) {
    ProcessCameraRotation(0.f, 1.f);
  }
}

void Camera::ProcessCameraRotation(float xoffset, float yoffset, GLboolean constrainPitch) {
  xoffset *= .1f;
  yoffset *= .1f;

  yaw += xoffset;
  pitch += yoffset;

  if (constrainPitch) {
    if (pitch > 89.0f) {
      pitch = 89.0f;
    }

    if (pitch < -89.0f) {
      pitch = -89.0f;
    }
  }

  updateCameraVectors();
}

void Camera::OnKeyboardDown(GLFWwindow *window, float deltaTime) {
  if (glfwGetKey(window, GLFW_KEY_W)) {
    transform.Position += front * moveSpeed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_A)) {
    transform.Position -= right * moveSpeed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_S)) {
    transform.Position -= front * moveSpeed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_D)) {
    transform.Position += right * moveSpeed * deltaTime;
  }

  if (glfwGetKey(window, GLFW_KEY_E)) {
    transform.Position.y += moveSpeed * deltaTime;
  } else if (glfwGetKey(window, GLFW_KEY_Q)) {
    transform.Position.y -= moveSpeed * deltaTime;
  }
}

glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(this->transform.Position, this->transform.Position + front, up);
}

void Camera::updateCameraVectors() {
  glm::vec3 frontVec;
  frontVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  frontVec.y = sin(glm::radians(pitch));
  frontVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  front = glm::normalize(frontVec);
  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}