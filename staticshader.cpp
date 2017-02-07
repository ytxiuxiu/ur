#include "staticshader.h"

StaticShader::StaticShader() :
    ShaderProgram(":/glsl/vertex.glsl", ":/glsl/fragment.glsl")
{

}

void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "normal");
}

void StaticShader::getUniformLocations()
{
    locationTransformation = getUniformLocation("transformation");
    locationProjection = getUniformLocation("projection");
    locationView = getUniformLocation("view");
    locationLightPosition = getUniformLocation("lightPosition");
    locationLightColour = getUniformLocation("lightColour");
    locationColour = getUniformLocation("colour");
    locationIsLight = getUniformLocation("isLight");
}

void StaticShader::loadTransformation(glm::mat4 transformation)
{
    loadMatrix(locationTransformation, transformation);
}

void StaticShader::loadProjection(glm::mat4 projection)
{
    loadMatrix(locationProjection, projection);
}

void StaticShader::loadView(Camera *camera)
{
    loadMatrix(locationView, Maths::createView(camera));
}

void StaticShader::loadLight(Light *light)
{
    loadVector(locationLightPosition, light->getPosition());
    loadVector(locationLightColour, light->getColour());
}

void StaticShader::loadColour(glm::vec3 colour)
{
    loadVector(locationColour, colour);
}

void StaticShader::loadIsLight(bool isLight)
{
    loadBool(locationIsLight, isLight);
}
