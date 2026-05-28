#ifndef MODEL_H
#define MODEL_H

#include <iostream>
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

    Model(std::string const path, bool gamma = false): gammaCorrection(gamma){
        loadModel(path);
    }

    void Draw(Shader &shader)
    {
        for (auto mesh : meshes)
        {
            mesh.Draw(shader);
        }
    }

private:
    void loadModel(std::string const path){
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

        // TODO: implements proper log functionality
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        directory = path.substr(0, path.find_last_of("/"));

        processNode(scene->mRootNode, scene);
    }

    void processNode(const aiNode *node, const aiScene *scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // NOTE: the node don`t contain the actual mesh but instead a indice of the mesh inside the meshes array from the scene
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

            meshes.push_back(processMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh processMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        // process vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; i++){
            Vertex vertex;

            // this vector is going to be reused for every attribute in the vertex
            glm::vec3 vector;

            // vertex position
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            // vertex normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }

            // vertex texture coords
            if (mesh->mTextureCoords[0])
            {
                glm::vec2 texCoordsVec;

                // texture coords
                texCoordsVec.x = mesh->mTextureCoords[0][i].x;
                texCoordsVec.y = mesh->mTextureCoords[0][i].y;

                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;

                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }else
            {
                vertex.TexCoords = glm::vec2(0.0f);
            }

            vertices.push_back(vertex);
        }

        // process indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // TODO: load textures

        return Mesh(vertices, indices, textures);
    }
};
#endif