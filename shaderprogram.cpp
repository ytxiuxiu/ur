#include "shaderprogram.h"

ShaderProgram::ShaderProgram(QString vertexShaderFilename, QString fragmentShaderFilename)
{
    programId = glCreateProgram();

    vertexShaderId = loadShader(vertexShaderFilename, GL_VERTEX_SHADER);
    fragmentShaderId = loadShader(fragmentShaderFilename, GL_FRAGMENT_SHADER);

    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);

    GLint result = GL_FALSE;
    GLint infoLogLength;

    // Check the program
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> error(infoLogLength + 1);
        glGetProgramInfoLog(programId, infoLogLength, NULL, &error[0]);
        std::string errorStr(error.begin(), error.end());
        qDebug() << errorStr.c_str();
    }
}


GLuint ShaderProgram::loadShader(QString filename, GLenum type)
{
    GLuint shaderId = glCreateShader(type);

    std::string code = readFile(filename).toUtf8().constData();
    GLchar const* files[] = { code.c_str() };
    GLint lengths[] = { (GLint) code.size() };

    glShaderSource(shaderId, 1, files, lengths);
    glCompileShader(shaderId);

    GLint result = GL_FALSE;
    GLint infoLogLength;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0)
    {
        std::vector<char> error(infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, NULL, &error[0]);
        std::string errorStr(error.begin(), error.end());
        qDebug() << errorStr.c_str();
    }
    return shaderId;
}

void ShaderProgram::start()
{
    glUseProgram(programId);
}

void ShaderProgram::stop()
{
    glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
    stop();

    glDetachShader(programId, vertexShaderId);
    glDeleteShader(vertexShaderId);

    glDetachShader(programId, fragmentShaderId);
    glDeleteShader(fragmentShaderId);

    glDeleteProgram(programId);
}

QString ShaderProgram::readFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return NULL;
    }
    QTextStream in(&file);
    return in.readAll();
}
