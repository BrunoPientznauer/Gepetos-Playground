#include "game.h"
#include "camera.h"
#include "renderable_object.h"
#include "scene_renderer.h"
#include <vector>

Game::Game():scene(createScene()) {

}

Game::~Game() {}

void Game::Init() {}

void Game::Update(float deltaTime) {
    scene.mainCamera.Update(deltaTime);
}

void Game::Render() { renderer.Render(this->scene); }

void Game::ProcessInputs(GLFWwindow* window, float deltaTime) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  scene.mainCamera.OnKeyboardDown(window, deltaTime);
}

void Game::mouseCallback(GLFWwindow *window, double xpos, double ypos) {
  scene.mainCamera.ProccessMouseMovement(window, xpos, ypos);
}

void Game::mouseButtonCallback(GLFWwindow *window, int button) {
    scene.mainCamera.OnMouseButtonDown(window, button);
}

Scene Game::createScene() {
    Camera camera(glm::vec3(0.f, .1f, 5.f), 1920.f/1080.f);

    RenderableObject backpack("assets/backpack/backpack.obj");
    RenderableObject backpack2("assets/backpack/backpack.obj");
    backpack.transform.Position = glm::vec3(0.0f, 1.f, 0.0f);
    backpack2.transform.Position = glm::vec3(4.0f, 1.f, 2.0f);

    std::vector<RenderableObject> objs;
    objs.push_back(backpack);
    objs.push_back(backpack2);

    return {.objects = objs, .mainCamera = camera};
}
