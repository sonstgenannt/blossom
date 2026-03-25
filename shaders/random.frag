#version 450 core

float funk(float n) {
    return fract(cos(n));
}

vec3 randomColor(int id) {
    float R = funk(float(id -1));
    float G = funk(float(id));
    float B = funk(float(id +1));
    return vec3(R, G, B);
}

layout (location = 0) out vec4 fColor;

void main() 
{
    int faceId = int(gl_PrimitiveID);

    fColor = vec4(randomColor(faceId), 1.0);
}
