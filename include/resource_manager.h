#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>

#include "shader.h"

class ResourceManager{
private:
    // resource storage
    static std::map<std::string, Shader> Shaders;

public:

    static Shader LoadShader(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr, std::string name);
    static Shader GetShader(std::string name);

    /**
     * Properly de allocate all loaded resources
     */
    static void Clear();

private:
    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile);
};

#endif