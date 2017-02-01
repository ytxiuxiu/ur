#include "maths.h"

mat4 Maths::createTransformation(vec3 translation, vec3 rotation, float scale)
{
    mat4 trans = translate(mat4(1), translation);
    mat4 rotX = rotate(mat4(1), radians(rotation.x), vec3(1, 0, 0));
    mat4 rotY = rotate(mat4(1), radians(rotation.y), vec3(0, 1, 0));
    mat4 rotZ = rotate(mat4(1), radians(rotation.z), vec3(0, 0, 1));
    mat4 rot = rotX * rotY * rotZ;
    mat4 sc = glm::scale(mat4(1), vec3(scale, scale, scale));

    return trans * rot * sc;
}
