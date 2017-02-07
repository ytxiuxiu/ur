#include "shaderprogram.h"

ShaderProgram::ShaderProgram(std::string vertexShaderFilename, std::string fragmentShaderFilename) {
    this->vertexShaderFilename = vertexShaderFilename;
    this->fragmentShaderFilename = fragmentShaderFilename;

    programId = glCreateProgram();
}

void ShaderProgram::compile()
{
    vertexShaderId = loadShader(vertexShaderFilename, GL_VERTEX_SHADER);
    fragmentShaderId = loadShader(fragmentShaderFilename, GL_FRAGMENT_SHADER);

    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    bindAttributes();

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

    getUniformLocations();
}


GLuint ShaderProgram::loadShader(std::string filename, GLenum type)
{
    GLuint shaderId = glCreateShader(type);

    std::string code = File::readFile(filename.c_str());
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

void ShaderProgram::bindAttribute(GLuint index, GLchar *name)
{
    glBindAttribLocation(programId, index, name);
}

GLint ShaderProgram::getUniformLocation(GLchar *name)
{
    return glGetUniformLocation(programId, name);
}

void ShaderProgram::loadFloat(GLint location, GLfloat value)
{
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(GLint location, glm::vec3 value)
{
    glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::loadBool(GLint location, bool value)
{
    glUniform1i(location, value ? 1 : 0);
}

void ShaderProgram::loadMatrix(GLint location, glm::mat4 value)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
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
