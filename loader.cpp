#include "loader.h"

Loader::Loader()
{
}

RawModel* Loader::loadToVao(vector<GLfloat> *vertices, vector<GLfloat> *normals,
                            vector<GLuint> *indices, vector<GLuint> shapeSizes)
{
    GLuint vaoId = createVao();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, vertices);
    storeDataInAttributeList(1, 3, normals);
    unbindVao();
    return new RawModel(vaoId, shapeSizes);
}

GLuint Loader::createVao()
{
    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    vaos.push_back(vaoId);
    glBindVertexArray(vaoId);
    return vaoId;
}

void Loader::bindIndicesBuffer(std::vector<GLuint> *indices)
{
    GLuint vboId;
    glGenBuffers(1, &vboId);
    vbos.push_back(vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLuint), indices->data(), GL_STATIC_DRAW);
}

void Loader::storeDataInAttributeList(int attributeNumber, int sizePerVertex, std::vector<GLfloat> *vertices)
{
    GLuint vboId;
    glGenBuffers(1, &vboId);
    vbos.push_back(vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(GLfloat), vertices->data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, sizePerVertex, GL_FLOAT, GL_FALSE, 0, (void*) 0);
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
