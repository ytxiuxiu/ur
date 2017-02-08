#ifndef STATICSHADER_H
#define STATICSHADER_H

#include <glm/glm.hpp>

#include "camera.h"
#include "maths.h"
#include "shaderprogram.h"
#include "light.h"

using namespace std;


class StaticShader : public ShaderProgram
{
public:
    StaticShader();
    void bindAttributes();
    void getUniformLocations();
    void loadTransformation(mat4 transformation);
    void loadProjection(mat4 projection);
    void loadView(Camera *camera);
    void loadLight(Light *light);
    void loadColour(vec3 colour);
    void loadIsLight(bool isLight);

private:
    GLint locationTransformation;
    GLint locationProjection;
    GLint locationView;
    GLint locationLightPosition;
    GLint locationLightColour;
    GLint locationColour;
    GLint locationIsLight;
};

#endif // STATICSHADER_H
