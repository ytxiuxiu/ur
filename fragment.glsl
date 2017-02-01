#version 330 core

in vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 out_Color;

uniform vec3 lightColour;

void main(void)
{
    vec3 unitSurfaceNormal = normalize(surfaceNormal);
    vec3 unitToLightVector = normalize(toLightVector);

    float brightness = max(dot(unitSurfaceNormal, unitToLightVector), 0);
    vec3 diffuse = brightness * lightColour * vec3(0.165, 0.451, 0.918);

    out_Color = vec4(diffuse, 1.0);

}
