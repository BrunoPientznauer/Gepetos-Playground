#include "game.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include "resource_manager.h"
#include <stb_image.h>


void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void renderGrid();

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float screen_width = SCR_WIDTH;
float screen_height = SCR_HEIGHT;

float deltaTime = 0.f;
float lastFrame = 0.f;

Game *g_game;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);


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
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    Game game;
    g_game = &game;

    // Configure global opengl state
    // ----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ResourceManager::LoadShader("resources/shaders/infinite_grid.vs","resources/shaders/infinite_grid.fs", nullptr,"grid");

    glfwShowWindow(window);
    glfwMaximizeWindow(window);
    
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
        game.ProcessInputs(window, deltaTime);

        game.Update(deltaTime);
        
        // render
        // ------
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game.Render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    ResourceManager::Clear();
    glfwTerminate();
    delete g_game;
    return 0;
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
    g_game->mouseCallback(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
    g_game->mouseButtonCallback(window, button);
}