#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <QtWidgets>
#include <glm/glm.hpp>

#include "rawmodel.h"


class Loader
{
public:
    Loader();
    RawModel* loadToVao(std::vector<GLfloat> *vertices);
    void cleanUp();

private:
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    GLuint createVao();
    void storeDataInAttributeList(int attributeNumber, std::vector<GLfloat> *data);
    void unbindVao();
};

#endif // LOADER_H
