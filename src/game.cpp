#include "game.h"
#include "basic_forms.h"
#include "camera.h"
#include "camera_handle.h"
#include "mesh.h"
#include "renderable_object.h"
#include "scene_renderer.h"
#include <glm/ext/vector_float3.hpp>
#include <vector>

Game::Game():m_scene(createScene()){
}

Game::~Game() {
}


void Game::Init() {}

void Game::Update() {
    this->m_cameraHandle.Update(&this->m_scene.mainCamera);
}

void Game::Render() {
  m_renderer.Render(this->m_scene); 
}

void Game::ProcessInputs(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  this->m_cameraHandle.OnKeyboardDown(&this->m_scene.mainCamera, window);
}

void Game::mouseCallback(GLFWwindow *window) {
  this->m_cameraHandle.ProccessMouseMovement(&this->m_scene.mainCamera, window);
}

void Game::mouseButtonCallback(GLFWwindow *window, int button) {
  this->m_cameraHandle.OnMouseButtonDown(&this->m_scene.mainCamera, window, button);
}

Scene Game::createScene() {
    Camera camera(glm::vec3(0.f, .1f, 5.f), 1920.f/1080.f);

    RenderableObject crab("assets/crab/crab.obj");
    crab.transform.Position = glm::vec3(0.0f, 1.f, 4.0f);

    std::vector<Mesh> terrainMeshes;
    terrainMeshes.push_back(GenerateQuad(6, 800.f));
    RenderableObject terrain(terrainMeshes);
    terrain.transform.Position += glm::vec3(-400.f, 0.f, -400.f);

    std::vector<RenderableObject> objs;
    objs.push_back(crab);
    objs.push_back(terrain);

    return {.objects = objs, .mainCamera = camera};
}
