#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <vector>
#include <QtWidgets>


class RawModel
{
public:
    RawModel(GLuint vaoId, GLuint vertexCount);
    GLuint getVaoId() { return vaoId; }
    GLuint getVertexCount() { return vertexCount; }

private:
    GLuint vaoId;
    GLuint vertexCount;
};

#endif // RAWMODEL_H
