#version 420 core
layout(location = 0) in vec3 aPos;

out vec3 worldPos;

uniform mat4 view;
uniform mat4 projection;

uniform vec3 cameraPos;

uniform float gridSize = 100.f;


const vec3 Pos[4] = vec3[4](
    vec3(-1.0f, 0.f, -1.f), // bottom left
    vec3( 1.0f, 0.f, -1.f), // bottom right
    vec3( 1.0f, 0.f,  1.f), // top right
    vec3(-1.0f, 0.f,  1.f)  // top left
);

const int Indices[6] = int[6](0, 2,1,2,0,3);

void main(){
    int Index = Indices[gl_VertexID];
    
    vec3 vPos = Pos[Index] * gridSize;

    vPos.x += cameraPos.x;
    vPos.z += cameraPos.z; 

    gl_Position = projection * view * vec4(vPos, 1.f);

    worldPos = vPos;
}