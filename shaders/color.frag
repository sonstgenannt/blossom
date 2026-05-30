#version 450 core

layout (location = 0) out vec4 fColor;

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

void main(void) 
{
  fColor = color;
}
