#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <game_object.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;

class Camera : public GameObject
{
public:
    /* DATA */
    float fov;
    float yaw;
    float pitch;

    /* Camera vectors */
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    float moveSpeed = 1.0f;

    Camera(glm::vec3 position, float fov = 45.f, float yaw = YAW, float pitch = PITCH, glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f)) : GameObject(position), fov(fov)
    {
        this->worldUp = worldUp;
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix(){
        return glm::lookAt(this->transform.Position, this->transform.Position + front, up);
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constainPitch = true){
        xoffset *= .1f;
        yoffset *= .1f;

        yaw   += xoffset;
        pitch += yoffset;

        if(constainPitch){
            if(pitch > 89.0f){
                pitch = 89.0f;
            }

            if(pitch < -89.0f){
                pitch = -89.0f;
            }
        }

        updateCameraVectors();
    }

    void OnKeyboardDown(GLFWwindow *window, float deltaTime){
      if (glfwGetKey(window, GLFW_KEY_W)) {
        transform.Position += front * moveSpeed * deltaTime;
      } else if (glfwGetKey(window, GLFW_KEY_A)) {
        transform.Position -= right * moveSpeed * deltaTime;
      } else if (glfwGetKey(window, GLFW_KEY_S)) {
        transform.Position -= front * moveSpeed * deltaTime;
      } else if (glfwGetKey(window, GLFW_KEY_D)) {
        transform.Position += right * moveSpeed * deltaTime;
      }

      if (glfwGetKey(window, GLFW_KEY_E)) {
        transform.Position.y += moveSpeed * deltaTime;
      } else if (glfwGetKey(window, GLFW_KEY_Q)) {
        transform.Position.y -= moveSpeed * deltaTime;
      }
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