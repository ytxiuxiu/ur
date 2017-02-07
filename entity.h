#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <glm/glm.hpp>

#include "rawmodel.h"

using namespace glm;


class Entity
{
public:
    Entity(RawModel *model, vec3 position, vec3 rotation, float scale,
           std::vector<vec3> colours, bool isLight) {
        this->model = model;
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        this->colours = colours;
        this->isLight = isLight;
    }

    Entity(RawModel *model) :
        Entity(model, vec3(0, 0, 0)) {}

    Entity(RawModel *model, vec3 position) :
        Entity(model, position, vec3(0, 0, 0)) {}

    Entity(RawModel *model, vec3 position, vec3 rotation) :
        Entity(model, position, rotation, 1) {}

    Entity(RawModel *model, vec3 position, vec3 rotation, float scale) :
        Entity(model, position, rotation, scale, std::vector<vec3>{ vec3(0.7, 0.7, 0.7) }) {}

    Entity(RawModel *model, vec3 position, vec3 rotation, float scale, std::vector<vec3> colours) :
        Entity(model, position, rotation, scale, colours, false) {}

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
    vec3 getPoistion() { return position; }
    void setPosition(vec3 position) { this->position = position; }
    vec3 getRotation() { return rotation; }
    void setRotation(vec3 rotation) { this->rotation = rotation; }
    float getScale() { return scale; }
    void setScale(float scale) { this->scale = scale; }
    std::vector<vec3> getColours() { return colours; }
    void setColours(std::vector<vec3> colours) { this->colours = colours; }
    bool getIsLight() { return isLight; }
    void setIsLight(bool light) { this->isLight = isLight; }

private:
    RawModel *model;
    vec3 position;
    vec3 rotation;
    float scale;
    std::vector<vec3> colours;
    bool isLight;
};

#endif // CUBE_H
