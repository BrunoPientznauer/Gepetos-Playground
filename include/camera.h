#ifndef CAMERA_H
#define CAMERA_H

#include <game_object.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;

class Camera : public GameObject
{
private:
    /* Camera vectors */
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

public:
    /* DATA */
    float fov;
    float yaw;
    float pitch;

    Camera(glm::vec3 position, float fov = 45.f, float yaw = YAW, float pitch = PITCH, glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f)) : GameObject(position), fov(fov)
    {
        this->worldUp = worldUp;
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix(){
        return glm::lookAt(this->position, this->position + front, up);
    }

private:
    void updateCameraVectors(){
        glm::vec3 frontVec;
        frontVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        frontVec.y = sin(glm::radians(pitch));
        frontVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        front = glm::normalize(frontVec);
        right = glm::normalize(glm::cross(front, worldUp));
        up    = glm::normalize(glm::cross(right, front));
    }
};



#endif