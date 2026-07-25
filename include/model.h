#pragma once

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

class Model{
public:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector <Texture> textures_loaded;
    bool gammaCorrection;

    Model(std::vector<Mesh> meshes, bool gamma = false);
    Model(std::string const path, bool gamma = false);

    void Draw(Shader &shader, glm::mat4 modelMatrix);

  private:
    void loadModel(std::string const path);

    void processNode(const aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *material,
                                              aiTextureType textureType,
                                              std::string typeName);
};

