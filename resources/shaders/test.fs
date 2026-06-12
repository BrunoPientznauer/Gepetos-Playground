#version 420 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main(){
    vec3 col = texture(texture_diffuse1, TexCoords).rgb;
    FragColor = vec4(col, 1.0);
}