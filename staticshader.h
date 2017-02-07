#ifndef STATICSHADER_H
#define STATICSHADER_H

#include <glm/glm.hpp>

#include "camera.h"
#include "maths.h"
#include "shaderprogram.h"
#include "light.h"


class StaticShader : public ShaderProgram
{
public:
    StaticShader();
    void bindAttributes();
    void getUniformLocations();
    void loadTransformation(glm::mat4 transformation);
    void loadProjection(glm::mat4 projection);
    void loadView(Camera *camera);
    void loadLight(Light *light);
    void loadColour(glm::vec3 colour);
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
