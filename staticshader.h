#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "shaderprogram.h"


class StaticShader : public ShaderProgram
{
public:
    StaticShader();
    void bindAttributes();
};

#endif // STATICSHADER_H
