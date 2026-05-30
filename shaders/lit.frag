#version 450 core

layout (location = 0) out vec4 fColor;

in vec4 Normal;
in vec4 FragPos;

uniform vec3 objectColor;

uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec4 norm = normalize(Normal);
    vec4 lightDir = normalize(vec4(lightPos, 1.0) - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    fColor = vec4(result, 1.0);
} 