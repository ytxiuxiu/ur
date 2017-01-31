#ifndef RAWMODEL_H
#define RAWMODEL_H


class RawModel
{
public:
    RawModel(int vaoId, int vertexCount);
    int getVaoId() { return vaoId; }
    int getVertexCount() { return vertexCount; }

private:
    int vaoId;
    int vertexCount;
};

#endif // RAWMODEL_H
