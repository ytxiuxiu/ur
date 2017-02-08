#ifndef KINEMATICLINK_H
#define KINEMATICLINK_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity.h"

using namespace std;


class KinematicLink
{
public:
    KinematicLink(Entity* entity, float theta, float d, float a, float alpha) {
        this->entity = entity;
        this->theta = theta;
        this->d = d;
        this->a = a;
        this->alpha = alpha;
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
        float theta = radians(this->theta);
        float alpha = radians(this->alpha);
        qDebug() << theta << alpha;
        return mat4(cos(theta), sin(theta), 0, 0,
                    -sin(theta) * cos(alpha), cos(theta) * cos(alpha), sin(alpha), 0,
                    sin(theta) * sin(alpha), -cos(theta) * sin(alpha), cos(alpha), 0,
                    a * cos(theta), a * sin(theta), d, 1);
    }

private:
    Entity* entity;
    float theta;
    float d;
    float a;
    float alpha;
};

#endif // KINEMATICLINK_H
