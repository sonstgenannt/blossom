#version 450 core

layout (location = 0) out vec4 fColor;

vec3 randomColor(int id) {
    float R = cos(float(id));
    float G = sin(float(id));
    float B = tan(float(id));
    return vec3(R, G, B);
}

void main() 
{
    int faceId = int(gl_PrimitiveID);

    fColor = vec4(randomColor(faceId), 1.0);
}
