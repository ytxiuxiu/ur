#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <QtWidgets>


class ShaderProgram
{
public:
    ShaderProgram(QString vertexShaderFilename, QString fragmentShaderFilename);
    void start();
    void stop();
    void cleanUp();

private:
    GLuint programId;
    GLuint vertexShaderId;
    GLuint fragmentShaderId;

    GLuint loadShader(QString filename, GLenum type);
    QString readFile(QString filename);
};

#endif // SHADERPROGRAM_H
