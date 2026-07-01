#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "transform.h"
#include <glm/glm.hpp>

class GameObject
{
public:
    /* Data */
    Transform transform;

    GameObject() {}
    GameObject(glm::vec3 position) { transform.Position = position; }
};



#endif