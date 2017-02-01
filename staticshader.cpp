#include "staticshader.h"

StaticShader::StaticShader() :
    ShaderProgram(":/glsl/vertex.glsl", ":/glsl/fragment.glsl")
{

}

void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
}

void StaticShader::getUniformLocations()
{
    locationTransformation = getUniformLocation("transformation");
    locationProjection = getUniformLocation("projection");
    locationView = getUniformLocation("view");
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
