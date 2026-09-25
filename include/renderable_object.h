#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "game_object.h"
#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "transform.h"
#include <string>
#include <vector>

class RenderableObject : public GameObject {
public:
  Model model;

  RenderableObject(std::string modelPath) : model(modelPath) {}
  RenderableObject(std::vector<Mesh> meshes) : model(meshes) {}

  void Draw(Shader &shader){
    model.Draw(shader, calculateModelMatrix(&transform));
  }
};

#endif