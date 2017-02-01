#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>

#include "rawmodel.h"


class Entity
{
public:
    Entity(RawModel *model, glm::vec3 position, glm::vec3 rotation, float scale) {
        this->model = model;
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }
    void increasePosition(float x, float y, float z) {
        this->position.x += x;
        this->position.y += y;
        this->position.z += z;
    }
    void increaseRotation(float x, float y, float z) {
        this->rotation.x += x;
        this->rotation.y += y;
        this->rotation.z += z;
    }
    RawModel *getModel() { return model; }
    glm::vec3 getPoistion() { return position; }
    glm::vec3 getRotation() { return rotation; }
    float getScale() { return scale; }
    void setScale(float scale) { this->scale = scale; }

private:
    RawModel *model;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;
};

#endif // CUBE_H
