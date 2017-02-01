#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <QtWidgets>
#include <glm/glm.hpp>


class ShaderProgram
{
public:
    ShaderProgram(QString vertexShaderFilename, QString fragmentShaderFilename);
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
    QString vertexShaderFilename;
    GLuint vertexShaderId;
    QString fragmentShaderFilename;
    GLuint fragmentShaderId;

    GLuint loadShader(QString filename, GLenum type);
    QString readFile(QString filename);
};

#endif // SHADERPROGRAM_H
