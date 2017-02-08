#ifndef MATHS_H
#define MATHS_H

#include <QtCore>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include "camera.h"

using namespace std;
using namespace glm;


class Maths
{
public:
    static mat4 createTransformation(vec3 translation, vec3 rotation, float scale);
    static mat4 createView(Camera *camera);
    static float degree(float radians) { return radians * 180 / M_PI; }
    static void print(mat4 matrix) {
        qDebug() << QString::number(matrix[0][0], 'f', 3) << QString::number(matrix[1][0], 'f', 3) << QString::number(matrix[2][0], 'f', 3) << QString::number(matrix[3][0], 'f', 3);
        qDebug() << QString::number(matrix[0][1], 'f', 3) << QString::number(matrix[1][1], 'f', 3) << QString::number(matrix[2][1], 'f', 3) << QString::number(matrix[3][1], 'f', 3);
        qDebug() << QString::number(matrix[0][2], 'f', 3) << QString::number(matrix[1][2], 'f', 3) << QString::number(matrix[2][2], 'f', 3) << QString::number(matrix[3][2], 'f', 3);
        qDebug() << QString::number(matrix[0][3], 'f', 3) << QString::number(matrix[1][3], 'f', 3) << QString::number(matrix[2][3], 'f', 3) << QString::number(matrix[3][3], 'f', 3);
        qDebug() << "";
    }
};

#endif // MATHS_H
