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

    return vec3(degree(yaw), degree(pitch), degree(roll));
}

vec4 Maths::getQuaternion(mat4 dhTransformation)
{
    float diagonal = dhTransformation[0][0] + dhTransformation[1][1] + dhTransformation[2][2];
    float x, y, z, w;
    if (diagonal > 0)
    {
        float w4 = std::sqrtf(diagonal + 1.0f) * 2.0f;
        w = w4 / 4.0f;
        x = (dhTransformation[2][1] - dhTransformation[1][2]) / w4;
        y = (dhTransformation[0][2] - dhTransformation[2][0]) / w4;
        z = (dhTransformation[1][0] - dhTransformation[0][1]) / w4;
    }
    else if ((dhTransformation[0][0] > dhTransformation[1][1]) &&
             (dhTransformation[0][0] > dhTransformation[2][2]))
    {
        float x4 = std::sqrtf(1.0f + dhTransformation[0][0] - dhTransformation[1][1] - dhTransformation[2][2]) * 2.0f;
        w = (dhTransformation[2][1] - dhTransformation[1][2]) / x4;
        x = x4 / 4.0f;
        y = (dhTransformation[0][1] + dhTransformation[1][0]) / x4;
        z = (dhTransformation[0][2] + dhTransformation[2][0]) / x4;
    }
    else if (dhTransformation[1][1] > dhTransformation[2][2])
    {
        float y4 = std::sqrtf(1.0f + dhTransformation[1][1] - dhTransformation[0][0] - dhTransformation[2][2]) * 2.0f;
        w = (dhTransformation[0][2] - dhTransformation[2][0]) / y4;
        x = (dhTransformation[0][1] + dhTransformation[1][0]) / y4;
        y = y4 / 4.0f;
        z = (dhTransformation[1][2] + dhTransformation[2][1]) / y4;
    } else {
        float z4 = std::sqrtf(1.0f + dhTransformation[2][2] - dhTransformation[0][0] - dhTransformation[1][1]) * 2.0f;
        w = (dhTransformation[1][0] - dhTransformation[0][1]) / z4;
        x = (dhTransformation[0][2] + dhTransformation[2][0]) / z4;
        y = (dhTransformation[1][2] + dhTransformation[2][1]) / z4;
        z = z4 / 4.0f;
    }
    float mag = std::sqrtf(w * w + x * x + y * y + z * z);
    w /= mag;
    x /= mag;
    y /= mag;
    z /= mag;
    return vec4(x, y, z, w);
}

mat4 Maths::getRotationMatric(vec4 quaternion)
{
    float x = quaternion.x;
    float y = quaternion.y;
    float z = quaternion.z;
    float w = quaternion.w;
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;
    float yz = y * z;
    float yw = y * w;
    float zw = z * w;
    float xSquared = x * x;
    float ySquared = y * y;
    float zSquared = z * z;
    mat4 matrix = {1 - 2 * (ySquared + zSquared), 2 * (xy - zw), 2 * (xz + yw), 0,
                   2 * (xy + zw), 1 - 2 * (xSquared + zSquared), 2 * (yz - xw), 0,
                   2 * (xz - yw), 2 * (yz + xw), 1 - 2 * (xSquared + ySquared), 0,
                   0, 0, 0, 1};
    return matrix;
}
