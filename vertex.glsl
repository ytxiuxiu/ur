#version 330 core

in vec3 position;
in vec3 normal;

out vec3 surfaceNormal;
out vec3 toLightVector;

uniform mat4 transformation;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightPosition;

void main(void)
{
    vec4 worldPosition = transformation * vec4(position, 1.0);
    gl_Position = projection * view * worldPosition;
    surfaceNormal = (transformation * vec4(normal, 0.0)).xyz;
    toLightVector = lightPosition - worldPosition.xyz;
}
