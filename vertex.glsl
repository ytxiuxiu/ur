#version 330 core

in vec3 position;

out vec3 colour;

uniform mat4 transformation;
uniform mat4 projection;
uniform mat4 view;

void main(void)
{
    gl_Position = projection * view * transformation * vec4(position.xyz, 1.0);
    colour = vec3(position.x + 0.5, 1.0, position.y + 0.5);
}
