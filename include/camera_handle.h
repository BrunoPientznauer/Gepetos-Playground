#pragma once

#include "camera.h"
#include "transform.h"

class CameraHandle {
public:
  virtual ~CameraHandle() = default;
  virtual void Update(Camera *camera) = 0;
  virtual void OnMouseButtonDown(Camera *camera, GLFWwindow *window, int button){}
  virtual void OnKeyboardDown(Camera *camera, GLFWwindow *window){}
  virtual void ProccessMouseMovement(Camera *camera, GLFWwindow *window){}
};

class FollowTargetCameraHandle : public CameraHandle {
private:
    Transform *target;
public:
  FollowTargetCameraHandle(Transform *target);
  void Update(Camera *camera) override;
};

class FreeCameraHandle : public CameraHandle{
private:
  bool  m_canRotate = false;
  bool  m_constrainPitch = true;
  float m_moveSpeed = 6.f;
  float m_rotateSpeed = 20.f;
  float m_pan = 5.f;

public:
  void Update(Camera *camera) override;
  void OnMouseButtonDown(Camera *camera, GLFWwindow *window, int button) override;
  void OnKeyboardDown(Camera *camera, GLFWwindow *window) override;
  void ProccessMouseMovement(Camera *camera, GLFWwindow *window) override;
private:
  void processCameraRotation(Camera *camera, float xOffset, float yOffset);
};