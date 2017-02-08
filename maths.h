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
    static vec4 getQuaternion(mat4 dhTransformation);
    static mat4 getRotationMatric(vec4 quaternion);
    static mat3 getRotationMatric(mat4 dhTransformation);
    static float degree(float radians) { return radians * 180 / M_PI; }
    static void print(mat4 matrix) {
        qDebug() << round(matrix[0][0]) << round(matrix[0][1]) << round(matrix[0][2]) << round(matrix[0][3]);
        qDebug() << round(matrix[1][0]) << round(matrix[1][1]) << round(matrix[1][2]) << round(matrix[1][3]);
        qDebug() << round(matrix[2][0]) << round(matrix[2][1]) << round(matrix[2][2]) << round(matrix[2][3]);
        qDebug() << round(matrix[3][0]) << round(matrix[3][1]) << round(matrix[3][2]) << round(matrix[3][3]);
        qDebug() << "";
    }
};

#endif // MATHS_H
