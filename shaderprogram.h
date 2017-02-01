#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <QtWidgets>
#include <glm/glm.hpp>

#include "file.h"


class ShaderProgram
{
public:
    ShaderProgram(std::string vertexShaderFilename, std::string fragmentShaderFilename);
    void compile();
    void start();
    void stop();
    void cleanUp();

protected:
    virtual void bindAttributes() = 0;
    void bindAttribute(GLuint index, GLchar *name);
    virtual void getUniformLocations() = 0;
    GLint getUniformLocation(GLchar *name);
    void loadFloat(GLint location, GLfloat value);
    void loadVector(GLint location, glm::vec3 value);
    void loadBool(GLint location, bool value);
    void loadMatrix(GLint location, glm::mat4 value);

private:
    GLuint programId;
    std::string vertexShaderFilename;
    GLuint vertexShaderId;
    std::string fragmentShaderFilename;
    GLuint fragmentShaderId;

    GLuint loadShader(std::string filename, GLenum type);
};

#endif // SHADERPROGRAM_H
