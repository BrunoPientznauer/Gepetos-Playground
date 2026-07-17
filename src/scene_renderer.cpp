#include "scene_renderer.h"
#include "mesh.h"
#include "resource_manager.h"
#include "transform.h"

Renderer::Renderer() {
  this->lightingPassShader = ResourceManager::LoadShader(
      "resources/shaders/test.vs", "resources/shaders/test.fs", nullptr,
      "test");
}

void Renderer::Render(Scene scene, Mesh teste){
    this->lightingPassShader.SetMatrix4("projection", scene.mainCamera.GetProjectionMatrix(), true);
    this->lightingPassShader.SetMatrix4("view", scene.mainCamera.GetViewMatrix(), true);

    for(auto obj : scene.objects){
        obj.Draw(this->lightingPassShader);
    }

    // TODO: remove
    Transform t;
    teste.Draw(this->lightingPassShader, t.getModelMatrix());
}
