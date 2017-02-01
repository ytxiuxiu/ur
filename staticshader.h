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

private:
    GLint locationTransformation;
};

#endif // STATICSHADER_H
