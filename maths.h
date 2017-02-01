#ifndef MATHS_H
#define MATHS_H

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

using namespace glm;


class Maths
{
public:
    Maths();
    static mat4 createTransformation(vec3 translation, vec3 rotation, float scale);

private:
    static float deg2Rad(float deg);
};

#endif // MATHS_H
