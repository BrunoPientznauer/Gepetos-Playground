#include "transform.h"

glm::mat4 calculateModelMatrix(Transform *transform){
    // 1. create identity matrix
    glm::mat4 modelMat = glm::mat4(1.0f);

    // 2. apply translation
    modelMat = glm::translate(modelMat, transform->Position);

    // 3. apply rotation
    modelMat = glm::rotate(modelMat, glm::radians(transform->Rotation.y), UP);
    modelMat = glm::rotate(modelMat, glm::radians(transform->Rotation.x), RIGHT);
    modelMat = glm::rotate(modelMat, glm::radians(transform->Rotation.z), FORWARD);

    // 4. apply scaling
    modelMat = glm::scale(modelMat, transform->Scale);

    return  modelMat;
}

