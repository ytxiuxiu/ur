#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader.h"
#include "objloader.h"


RawModel* ObjLoader::loadObjModel(string fileContent, Loader *loader)
{
    vector<GLuint> shapeSizes;

    tinyobj::attrib_t attrib;
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> materials;
    string err;

    istringstream inBaseFile(fileContent.c_str());
    tinyobj::LoadObj(&attrib, &shapes, &materials, &err, &inBaseFile);

    vector<GLuint> vertexIndices;
    vector<GLuint> normalIndices;

    for (unsigned long j = 0; j < shapes.size(); j++)
    {
        shapeSizes.push_back(shapes[j].mesh.indices.size());
        for (unsigned long i = 0; i < shapes[j].mesh.indices.size(); i++)
        {
            vertexIndices.push_back((GLuint) shapes[j].mesh.indices[i].vertex_index);
            normalIndices.push_back((GLuint) shapes[j].mesh.indices[i].normal_index);
        }
    }

    vector<GLfloat> vertices(vertexIndices.size() * 3);
    vector<GLfloat> normals(vertexIndices.size() * 3);

    for (unsigned long i = 0; i < vertexIndices.size(); i++)
    {
        int vertexPostion = vertexIndices[i];
        int normalPosition = normalIndices[i];

        vertices[i * 3] = attrib.vertices[vertexPostion * 3];
        vertices[i * 3 + 1] = attrib.vertices[vertexPostion * 3 + 1];
        vertices[i * 3 + 2] = attrib.vertices[vertexPostion * 3 + 2];
        normals[i * 3] = attrib.normals[normalPosition * 3];
        normals[i * 3 + 1] = attrib.normals[normalPosition * 3 + 1];
        normals[i * 3 + 2] = attrib.normals[normalPosition * 3 + 2];
    }

    return loader->loadToVao(&vertices, &normals, &vertexIndices, shapeSizes);
}
