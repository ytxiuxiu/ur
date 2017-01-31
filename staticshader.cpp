#include "staticshader.h"

StaticShader::StaticShader() :
    ShaderProgram(":/glsl/vertex.glsl", ":/glsl/fragment.glsl")
{

}

void StaticShader::bindAttributes()
{

}
