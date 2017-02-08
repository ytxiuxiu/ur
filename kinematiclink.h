#ifndef KINEMATICLINK_H
#define KINEMATICLINK_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity.h"


class KinematicLink
{
public:
    KinematicLink(Entity* entity, float theta, float d, float a, float alpha, float rotate) {
        this->entity = entity;
        this->theta = theta;
        this->d = d;
        this->a = a;
        this->alpha = alpha;
        this->rotate = rotate;
    }
    Entity* getEntity() { return entity; }
    void setEntity(Entity* entity) { this->entity = entity; }
    float getTheta() { return theta; }
    void setTheta(float theta) { this->theta = theta; }
    float getD() { return d; }
    void setD(float d) { this->d = d; }
    float getA() { return a; }
    void setA(float a) { this->a = a; }
    float getAlpha() { return alpha; }
    void setAlpha(float alpha) { this->alpha = alpha; }
    mat4 getMatrix() {
        return mat4(std::cos(radians(theta)), -std::sin(radians(theta)) * std::cos(radians(alpha)), std::sin(radians(theta)) * std::sin(radians(alpha)), a * std::cos(radians(theta)),
                    std::sin(radians(theta)), std::cos(radians(theta)) * std::cos(radians(alpha)), -std::cos(radians(theta)) * std::sin(radians(alpha)), a * std::sin(radians(theta)),
                    0, std::sin(radians(alpha)), std::cos(radians(alpha)), d,
                    0, 0, 0, 1);
    }
    float getRotate() { return rotate; }
    void setRotate(float rotate) { this->rotate = rotate; }

private:
    Entity* entity;
    float theta;
    float d;
    float a;
    float alpha;
    float rotate;
};

#endif // KINEMATICLINK_H
