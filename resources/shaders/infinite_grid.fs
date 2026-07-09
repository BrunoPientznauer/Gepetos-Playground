#version 420 core



out vec4 FragColor;

in vec3 worldPos;

uniform float gridCellSize = 0.025f;
uniform float gridSize = 100.f;
uniform float gridMinPixelsBetweenCells = 2.0f;
uniform vec4 gridColorThin = vec4(0.5f, 0.5f, 0.5f, 1.f);
uniform vec4 gridColorThick = vec4(0.f, 0.f, 0.f, 1.f);
uniform vec3 cameraPos;

vec2 satv(vec2 x)
{
    vec2 v = clamp(x, vec2(0.0), vec2(1.0));
    return v;
}

float satf(float x)
{
    float f = clamp(x, 0.0, 1.0);
    return f;
}

float max2(vec2 v)
{
    float f = max(v.x, v.y);
    return f;
}

float log10(float x)
{
    float f = log(x) / log(10.0);
    return f;
}

void main(){


    vec2 dvx = vec2(dFdx(worldPos.x), dFdy(worldPos.x));
    vec2 dvy = vec2(dFdx(-worldPos.z), dFdy(-worldPos.z));

    float lx = length(dvx);
    float ly = length(dvy);

    vec2 dudv = vec2(lx, ly);

    float l = length(dudv);

    float LOD = max(0.0, log10(l * gridMinPixelsBetweenCells / gridCellSize) + 1.0f); 

    float gridCellSizeLod0 = gridCellSize * pow(10.f, floor(LOD));
    float gridCellSizeLod1 = gridCellSizeLod0 * 10.f;
    float gridCellSizeLod2 = gridCellSizeLod1 * 10.f;

    dudv *= 4.0f;

    vec2 mod_div_dudv = mod(worldPos.xz, gridCellSizeLod0) / dudv;
    float Lod0a = max2(vec2(1.0) - abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)));

    mod_div_dudv = mod(worldPos.xz, gridCellSizeLod1) / dudv;
    float Lod1a = max2(vec2(1.0f) - abs(satv(mod_div_dudv) * 2.0f - vec2(1.0f)));

    mod_div_dudv = mod(worldPos.xz, gridCellSizeLod2) / dudv;
    float Lod2a = max2(vec2(1.0f) - abs(satv(mod_div_dudv) * 2.0f - vec2(1.0f)));

    float LOD_fade = fract(LOD);

    vec4 color;

    if(Lod2a > 0.0f){
        color = gridColorThick;    
        color.a *= Lod2a;
    }else{
        if(Lod1a > 0.0f){
            color = mix(gridColorThick, gridColorThin, LOD_fade);
            color.a *= Lod1a;
        }else{
            color = gridColorThin;
            color.a *= (Lod0a * (1.0f - LOD_fade));
        }
    }

    float opacityFallof = (1.0f - satf(length(worldPos.xz - cameraPos.xz) / gridSize));
    color.a *= opacityFallof;

    FragColor = color;
}