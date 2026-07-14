#pragma once

#include "renderable_object.h"
#include "camera.h"
#include <vector>

struct Scene{
    std::vector<RenderableObject> objects;
    Camera mainCamera;
};

class Renderer {
public:
  Renderer();

  void Render(Scene scene);

private:
  Shader lightingPassShader;
};