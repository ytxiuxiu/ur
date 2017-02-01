#ifndef MATHS_H
#define MATHS_H

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
};

#endif // MATHS_H
