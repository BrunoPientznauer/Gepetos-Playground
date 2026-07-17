#include "basic_forms.h"
#include "mesh.h"
#include <glm/ext/vector_float3.hpp>
#include <vector>

Mesh GenerateQuad(int numVertices, float size){
    int count = numVertices * numVertices;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for(unsigned int z = 0; z < numVertices; z++){
        for(unsigned int x = 0; x < numVertices; x++){
            Vertex v;

            // 1. generate positions
            float xPos = ((float)x / (numVertices - 1)) * size;
            float zPos = ((float)z / (numVertices - 1)) * size;
            v.Position = glm::vec3(xPos, 0.f, zPos);
            // 2. generate normals
            v.Normal = glm::vec3(0.f, 1.f, 0.f);
            // 3. generate texture coordinations
            float xCoord = (float)x /(numVertices - 1);
            float yCoord = (float)z / (numVertices - 1);
            v.TexCoords = glm::vec2(xCoord, yCoord);

            vertices.push_back(v);
        }
    }

    for(unsigned int iz = 0; iz < numVertices; iz++){
        for(unsigned int ix = 0; ix < numVertices; ix++){
            int topLeft = (iz * numVertices) + ix;
            int topRight = topLeft + 1;
            int bottomLeft = ((iz + 1) * numVertices) + ix;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }


    return  Mesh(vertices, indices);
}