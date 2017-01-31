#include "loader.h"

Loader::Loader()
{
}

RawModel* Loader::loadToVao(std::vector<GLfloat> *vertices)
{
    GLuint vaoId = createVao();
    storeDataInAttributeList(0, vertices);
    unbindVao();
    return new RawModel(vaoId, vertices->size() / 3);
}

GLuint Loader::createVao()
{
    GLuint vaoId;
    vaos.push_back(vaoId);
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    return vaoId;
}

void Loader::storeDataInAttributeList(int attributeNumber, std::vector<GLfloat> *vertices)
{
    GLuint vboId;
    vbos.push_back(vboId);
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(GLfloat), vertices->data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::cleanUp()
{
    for (unsigned long i = 0; i < vaos.size(); i++)
    {
        glDeleteVertexArrays(1, &vaos[i]);
    }
    for (unsigned long i = 0; i < vbos.size(); i++)
    {
        glDeleteBuffers(1, &vbos[i]);
    }
}

void Loader::unbindVao()
{
    glBindVertexArray(0);
}
