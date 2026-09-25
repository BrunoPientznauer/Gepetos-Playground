#include "camera_handle.h"
#include "globals.h"
#include "transform.h"
#include "time.h"

FollowTargetCameraHandle::FollowTargetCameraHandle(Transform *target)
    : target(target) {}

void FollowTargetCameraHandle::Update(Camera *camera) {}

#pragma region FreeCameraHandle

void FreeCameraHandle::Update(Camera *camera) {
    if (MouseContext::mouseOnRightEdge) {
    processCameraRotation(camera, this->m_pan, 0.f);
  } else if (MouseContext::mouseOnLeftEdge) {
    processCameraRotation(camera, -this->m_pan, 0.f);
  }

  if (MouseContext::mouseOnUpperdge) {
    processCameraRotation(camera, 0.f, this->m_pan);
  } else if (MouseContext::mouseOnLowerEdge) {
    processCameraRotation(camera, 0.f, -this->m_pan);
  }
}

void FreeCameraHandle::OnMouseButtonDown(Camera *camera, GLFWwindow *window, int button) {
  m_canRotate = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

void FreeCameraHandle::OnKeyboardDown(Camera *camera, GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W)) {
    camera->transform.Position += camera->front * this->m_moveSpeed * Time::GetDeltaTime();
  } else if (glfwGetKey(window, GLFW_KEY_A)) {
   camera->transform.Position -= camera->right * this->m_moveSpeed * Time::GetDeltaTime();
  } else if (glfwGetKey(window, GLFW_KEY_S)) {
    camera->transform.Position -= camera->front * this->m_moveSpeed * Time::GetDeltaTime();
  } else if (glfwGetKey(window, GLFW_KEY_D)) {
    camera->transform.Position += camera->right * this->m_moveSpeed * Time::GetDeltaTime();
  }

  if (glfwGetKey(window, GLFW_KEY_E)) {
    camera->transform.Position.y += this->m_moveSpeed * Time::GetDeltaTime();
  } else if (glfwGetKey(window, GLFW_KEY_Q)) {
    camera->transform.Position.y -= this->m_moveSpeed * Time::GetDeltaTime();
  }
}

void FreeCameraHandle::ProccessMouseMovement(Camera *camera, GLFWwindow *window) {
  int screenWidth;
  int screenHeight;

  glfwGetWindowSize(window, &screenWidth, &screenHeight);

  float xOffset = MouseContext::posX - MouseContext::lastMouseX;
  float yOffset = MouseContext::lastMouseY - MouseContext::posY;

  processCameraRotation(camera, xOffset, yOffset);
}

void FreeCameraHandle::processCameraRotation(Camera *camera, float xOffset, float yOffset) {
  if (!m_canRotate)
    return;

  xOffset *= .1f;
  yOffset *= .1f;

  camera->yaw   += xOffset * this->m_rotateSpeed * Time::GetDeltaTime();
  camera->pitch += yOffset * this->m_rotateSpeed * Time::GetDeltaTime();

  if (m_constrainPitch) {
    if (camera->pitch > 89.0f) {
      camera->pitch = 89.0f;
    }

    if (camera->pitch < -89.0f) {
      camera->pitch = -89.0f;
    }
  }

  updateCameraVectors(camera);
}
#pragma endregion