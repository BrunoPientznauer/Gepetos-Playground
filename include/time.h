#pragma once

class Time{
private:
  static float deltaTime;

public:
  static float GetDeltaTime();

  static void Update(float currentFrame, float lastFrame);
};