#include "time.h"

float Time::deltaTime;

void Time::Update(float currentFrame, float lastFrame) {
  deltaTime = currentFrame - lastFrame;
}

float Time::GetDeltaTime() { return deltaTime; }
