#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, Shader>  ResourceManager::s_shaders;

Shader ResourceManager::LoadShader(const char *vertexSource, const char *fragmentSource, const char *geometrySource, std::string name)
{
    s_shaders[name] = loadShaderFromFile(vertexSource, fragmentSource, geometrySource);
    return s_shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return s_shaders[name];
}

void ResourceManager::Clear()
{
    for(auto iter : s_shaders){
        glDeleteShader(iter.second.ID);
    }
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile){
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        // read file buffer
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        if(gShaderFile != nullptr){
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();

    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

    return shader;
}
