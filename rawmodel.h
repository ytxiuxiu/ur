#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <vector>
#include <QtWidgets>

using namespace std;


class RawModel
{
public:
    RawModel(GLuint vaoId, vector<GLuint> shapeSizes) {
        this->vaoId = vaoId;
        this->shapeSizes = shapeSizes;
    }
    GLuint getVaoId() { return vaoId; }
    vector<GLuint> getShapeSizes() { return shapeSizes; }

private:
    GLuint vaoId;
    vector<GLuint> shapeSizes;
};

#endif // RAWMODEL_H
