#include "camera.h"
#include "transform.h"
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 position, float aspectRatio, float fov, float yaw, float pitch, glm::vec3 worldUp): transform(position), fov(fov), aspectRatio(aspectRatio) {
  this->worldUp = worldUp;
  this->yaw = yaw;
  this->pitch = pitch;
  updateCameraVectors(this);
}

glm::mat4 CameraProjectionMatrix(Camera *camera) {
  return glm::perspective(camera->fov, camera->aspectRatio, 0.1f, 1000.f);
}

glm::mat4 CameraViewMatrix(Camera *camera) {
    return glm::lookAt(camera->transform.Position, camera->transform.Position + camera->front, camera->up);
}

void updateCameraVectors(Camera *camera) {
  glm::vec3 frontVec;
  frontVec.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
  frontVec.y = sin(glm::radians(camera->pitch));
  frontVec.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));

  camera->front = glm::normalize(frontVec);
  camera->right = glm::normalize(glm::cross(camera->front, camera->worldUp));
  camera->up = glm::normalize(glm::cross(camera->right, camera->front));
}