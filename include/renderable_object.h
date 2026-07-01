#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "game_object.h"
#include "model.h"
#include "shader.h"
#include <string>

class RenderableObject : public GameObject {
public:
  Model model;

  RenderableObject(std::string modelPath) : model(modelPath) {}

  void Draw(Shader &shader){
    model.Draw(shader, transform.getModelMatrix());
  }
};

#endif