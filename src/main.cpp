#include "scene_renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <vector>

#include "renderable_object.h"
#include "resource_manager.h"
#include "camera.h"
#include <stb_image.h>


void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void setupQuad();

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float screen_width = SCR_WIDTH;
float screen_height = SCR_HEIGHT;

Camera camera(glm::vec3(0.f, 0.1f, 0.0f), screen_width/screen_height);
Scene scene = {.mainCamera = camera};

float deltaTime = 0.f;
float lastFrame = 0.f;

float lastMouseX;
float lastMouseY;
bool firstMouse = true;

unsigned int quadVAO, quadVBO;


int main()
{
    camera.moveSpeed = 2.0f;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    screen_width = mode->height;
    screen_height  = mode->width;

    scene.mainCamera.aspectRatio = screen_height/screen_width;

    stbi_set_flip_vertically_on_load(true);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Gepetos-Playground", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // Configure global opengl state
    // ----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Renderer renderer;
    RenderableObject backpack("assets/backpack/backpack.obj");
    RenderableObject backpack2("assets/backpack/backpack.obj");
    backpack2.transform.Position = glm::vec3(4.0f, 0.f, 2.0f);

    Shader gridShader = ResourceManager::LoadShader("resources/shaders/infinite_grid.vs","resources/shaders/infinite_grid.fs", nullptr,"infinite_grid");
    scene.objects.push_back(backpack);
    scene.objects.push_back(backpack2);

    glfwShowWindow(window);

    setupQuad();
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        
        // calculates delta time
        auto currentFrame =  static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        // -----
        processInput(window);

        scene.mainCamera.Update(deltaTime);
        
        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.Render(scene);

        // render Grid
        // -----------
        gridShader.Use();
        gridShader.SetMatrix4("projection", scene.mainCamera.GetProjectionMatrix(), true);
        gridShader.SetMatrix4("view", scene.mainCamera.GetViewMatrix(), true);
        gridShader.SetVector3f("cameraPos", scene.mainCamera.transform.Position);
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

void setupQuad(){
  float vertices[] = {
      // Coordenadas   // Textura
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // Superior Esquerdo
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Inferior Esquerdo
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Superior Direito
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f  // Inferior Direito
  };

  glGenVertexArrays(1, &quadVAO);
  glGenBuffers(1, &quadVBO);

  glBindVertexArray(quadVAO);

  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    scene.mainCamera.OnKeyboardDown(window, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    screen_width = width;
    screen_height = height;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos){
   scene.mainCamera.ProccessMouseMovement(window, xpos, ypos);
}