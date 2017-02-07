#version 330 core

in vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 out_Color;

uniform vec3 lightColour;
uniform vec3 colour;
uniform bool isLight;

void main(void)
{
    vec3 unitSurfaceNormal = normalize(surfaceNormal);
    vec3 unitToLightVector = normalize(toLightVector);

    if (isLight)
    {
        out_Color = vec4(colour, 1.0);
    }
    else
    {
        float brightness = max(dot(unitSurfaceNormal, unitToLightVector), 0);
        vec3 diffuse = brightness * lightColour * colour;
        out_Color = vec4(diffuse, 1.0);
    }



}
