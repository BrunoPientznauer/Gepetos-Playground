#ifndef MESH_H
#define MESH_H

#include <cstddef>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "shader.h"

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture{
    unsigned int Id;
    std::string type;
    std::string path;
};


class Mesh{
public:
    //mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    // render data
    unsigned int VAO, VBO, EBO;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures.clear();

        setupMesh();
    }

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setupMesh();
    }

    void Draw(Shader &shader, glm::mat4 modelMatrix)
    {
        shader.Use();

        shader.SetMatrix4("model", modelMatrix);

        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        if (!textures.empty()) {
          for (unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = textures[i].type;

            if (name == "texture_diffuse")
              number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
              number = std::to_string(specularNr++);
            else if (name == "texture_normal")
              number = std::to_string(normalNr++);
            else if (name == "texture_height")
              number = std::to_string(heightNr++);

            shader.SetInteger((name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].Id);
          }
        }else{
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, 0);
        }

        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

        // sets configs to default
        glActiveTexture(GL_TEXTURE0);
    }
private:

    /**
     * creates the VBO, VAO & EBO and sets the attributes to be applied in the shaders
     */
    void setupMesh()
    {
        // create buffers
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);
        // load data into vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // sets vertex attribute pointers

        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
        // vertex Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));
        // texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));
        // tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Tangent));
        // bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Bitangent));

        glBindVertexArray(0);
    }
};
#endif