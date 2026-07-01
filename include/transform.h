#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>

#define UP      glm::vec3(0.0f, 1.0f, 0.0f)
#define RIGHT   glm::vec3(1.0f, 0.0f, 0.0f)
#define FORWARD glm::vec3(0.0f, 0.0f, 1.0f)

class Transform{
public:
  glm::vec3 Position;
  glm::vec3 Rotation;
  glm::vec3 Scale;

  Transform():Position(glm::vec3(0.f)), Rotation(glm::vec3(0.f)), Scale(glm::vec3(1.f)){}

  glm::mat4 getModelMatrix(){
    // 1. create identity matrix
    glm::mat4 modelMat = glm::mat4(1.0f);

    // 2. apply translation
    modelMat = glm::translate(modelMat, Position);

    // 3. apply rotation
    modelMat = glm::rotate(modelMat, glm::radians(Rotation.y), UP);
    modelMat = glm::rotate(modelMat, glm::radians(Rotation.x), RIGHT);
    modelMat = glm::rotate(modelMat, glm::radians(Rotation.z), FORWARD);

    // 4. apply scaling
    modelMat = glm::scale(modelMat, Scale);

    return  modelMat;
  }
};

#endif