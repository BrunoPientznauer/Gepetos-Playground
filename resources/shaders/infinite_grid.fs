#version 420 core

out vec4 FragColor;

in vec3 worldPos;

uniform float gridCellSize = 0.05f;
uniform vec4 gridColorThin = vec4(0.5f, 0.5f, 0.5f, 1.f);
uniform vec4 gridColorThick = vec4(0.f, 0.f, 0.f, 1.f);

void main(){


    vec2 dvx = vec2(dFdx(worldPos.x), dFdy(worldPos.x));
    vec2 dvy = vec2(dFdx(-worldPos.z), dFdy(-worldPos.z));

    float lx = length(dvx);
    float ly = length(dvy);

    vec2 dudv = vec2(lx, ly);
    dudv *= 4.0f;

    float Lod0a = max( 1.0 - mod(worldPos.x, gridCellSize) / dudv.x, 1.0 - mod(-worldPos.z, gridCellSize) / dudv.y);

    vec4 color;

    color = gridColorThick;
    color.a *= Lod0a;

    FragColor = color;
}