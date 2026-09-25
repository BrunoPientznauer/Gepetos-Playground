#ifndef CAMERA_H
#define CAMERA_H

#include "transform.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <game_object.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;

struct Camera{
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

  Transform transform;

  Camera(glm::vec3 position, float aspectRatio, float fov = 45.f,
         float yaw = YAW, float pitch = PITCH,
         glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));
};

glm::mat4 CameraViewMatrix(Camera *camera);

glm::mat4 CameraProjectionMatrix(Camera *camera);

void updateCameraVectors(Camera *camera);


#endif