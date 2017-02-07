#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <QtWidgets>
#include <glm/glm.hpp>

#include "rawmodel.h"

using namespace std;


class Loader
{
public:
    Loader();
    RawModel* loadToVao(vector<GLfloat> *vertices, vector<GLfloat> *normals,
                        vector<GLuint> *indices, vector<GLuint> shapeSizes);
    void cleanUp();

private:
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    GLuint createVao();
    void bindIndicesBuffer(std::vector<GLuint> *indices);
    void storeDataInAttributeList(int attributeNumber, int sizePerVertex, std::vector<GLfloat> *data);
    void unbindVao();
};

#endif // LOADER_H
