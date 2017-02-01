#ifndef STATICSHADER_H
#define STATICSHADER_H

#include <glm/glm.hpp>

#include "shaderprogram.h"


class StaticShader : public ShaderProgram
{
public:
    StaticShader();
    void bindAttributes();
    void getUniformLocations();
    void loadTransformation(glm::mat4 transformation);
    void loadProjection(glm::mat4 projection);

private:
    GLint locationTransformation;
    GLint locationProjection;
};

#endif // STATICSHADER_H
