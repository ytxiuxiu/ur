#version 330 core

in vec3 position;

out vec3 colour;

uniform mat4 transformation;

void main(void)
{
    gl_Position = transformation * vec4(position.xyz, 1.0);
    colour = vec3(position.x + 0.5, 1.0, position.y + 0.5);
}
