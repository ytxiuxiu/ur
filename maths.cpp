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

mat4 Maths::createView(Camera *camera)
{
    mat4 rotX = rotate(mat4(1), radians(camera->getRotation().x), vec3(1, 0, 0));
    mat4 rotY = rotate(mat4(1), radians(camera->getRotation().y), vec3(0, 1, 0));
    mat4 rotZ = rotate(mat4(1), radians(camera->getRotation().z), vec3(0, 0, 1));
    mat4 rot = rotX * rotY * rotZ;
    mat4 trans = translate(mat4(1), vec3(-camera->getPosition().x, -camera->getPosition().y, -camera->getPosition().z));

    return rot * trans;
}

mat4 Maths::createDhTransformation(float d, float theta, float a, float alpha)
{
    return mat4(std::cos(radians(theta)), -std::sin(radians(theta)) * std::cos(radians(alpha)), std::sin(radians(theta)) * std::sin(radians(alpha)), a * std::cos(radians(theta)),
                std::sin(radians(theta)), std::cos(radians(theta)) * std::cos(radians(alpha)), -std::cos(radians(theta)) * std::sin(radians(alpha)), a * std::sin(radians(theta)),
                0, std::sin(radians(alpha)), std::cos(radians(alpha)), d,
                0, 0, 0, 1);
}

mat3 Maths::getRotationMatric(mat4 dhTransformation)
{
    return mat3(dhTransformation[0][0], dhTransformation[0][1], dhTransformation[0][2],
                dhTransformation[1][0], dhTransformation[1][1], dhTransformation[1][2],
                dhTransformation[2][0], dhTransformation[2][1], dhTransformation[2][2]);
}

vec3 Maths::getPosition(mat4 dhTransformation)
{
    return vec3(dhTransformation[1][3], dhTransformation[2][3], dhTransformation[0][3]);
}

vec3 Maths::getRotation(mat4 dhTransformation)
{
    float yaw, pitch, roll;

    if (dhTransformation[0][0] == 1.0f || dhTransformation[0][0] == -1.0f)
    {
        yaw = std::atan2f(dhTransformation[0][2], dhTransformation[2][3]);
        pitch = 0;
    }
    else
    {
        yaw = std::atan2(-dhTransformation[2][0], dhTransformation[0][0]);
        pitch = std::asin(dhTransformation[1][0]);
    }
    roll = std::atan2(-dhTransformation[1][2], dhTransformation[1][1]);

    qDebug() << "yaw(z->y)" << yaw << "pitch(y->x)" << pitch << "roll(x->z)" << roll;

    return vec3(degree(yaw), degree(pitch), degree(roll));
}

//vec4 Maths::quaternion(vec3 rotation)
//{
//    double t0 = std::cos(yaw * 0.5);
//    double t1 = std::sin(yaw * 0.5);
//    double t2 = std::cos(roll * 0.5);
//    double t3 = std::sin(roll * 0.5);
//    double t4 = std::cos(pitch * 0.5);
//    double t5 = std::sin(pitch * 0.5);

//    q.w() = t0 * t2 * t4 + t1 * t3 * t5;
//    q.x() = t0 * t3 * t4 - t1 * t2 * t5;
//    q.y() = t0 * t2 * t5 + t1 * t3 * t4;
//    q.z() = t1 * t2 * t4 - t0 * t3 * t5;
//}

//vec3
