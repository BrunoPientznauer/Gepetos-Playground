#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>

class GameObject
{
public:
    /* Data */
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    GameObject() : position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f)), scale(glm::vec3(1.0f)){}
    GameObject(glm::vec3 position) : position(position), rotation(glm::vec3(0.0f)){}
};



#endif