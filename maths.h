#ifndef MATHS_H
#define MATHS_H

#include <QtCore>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include "camera.h"

using namespace glm;


class Maths
{
public:
    static mat4 createTransformation(vec3 translation, vec3 rotation, float scale);
    static mat4 createView(Camera *camera);
    static mat4 createDhTransformation(float d, float theta, float a, float alpha);
    static vec3 getPosition(mat4 dhTransformation);
    static vec3 getRotation(mat4 dhTransformation);
    static mat3 getRotationMatric(mat4 dhTransformation);
    static float degree(float radians) { return radians * 180 / M_PI; }
//    static vec4 quaternion(vec3 rotation);
//    static vec3 rotation(vec4 quaternion);
};

#endif // MATHS_H
