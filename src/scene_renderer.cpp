#include "scene_renderer.h"
#include "camera.h"
#include "resource_manager.h"

Renderer::Renderer() {
  this->lightingPassShader = ResourceManager::LoadShader(
      "resources/shaders/test.vs", "resources/shaders/test.fs", nullptr,
      "test");
}

void Renderer::Render(Scene scene){
    this->lightingPassShader.SetMatrix4("projection", CameraProjectionMatrix(&scene.mainCamera), true);
    this->lightingPassShader.SetMatrix4("view", CameraViewMatrix(&scene.mainCamera), true);

    for(auto obj : scene.objects){
        obj.Draw(this->lightingPassShader);
    }
}
