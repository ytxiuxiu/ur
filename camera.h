#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

using namespace glm;


class Camera
{
public:
    Camera(vec3 position, vec3 rotation) {
        this->position = position;
        this->rotation = rotation;
    }
    void increasePostion(float x, float y, float z) {
        position.x += x;
        position.y += y;
        position.z += z;
    }
    void increaseRotation(float x, float y, float z) {
        rotation.x += x;
        rotation.y += y;
        rotation.z += z;
    }
    vec3 getPosition() { return position; }
    void setPosition(vec3 position) { this->position = position; }
    vec3 getRotation() { return rotation; }
    void setRotation(vec3 rotation) { this->rotation = rotation; }

private:
    vec3 position;
    vec3 rotation;
};

#endif // CAMERA_H
