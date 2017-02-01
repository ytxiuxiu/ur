#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

using namespace glm;


class Light
{
public:
    Light(vec3 position, vec3 colour) {
        this->position = position;
        this->colour = colour;
    }
    vec3 getPosition() { return position; }
    vec3 getColour() { return colour; }

private:
    vec3 position;
    vec3 colour;
};

#endif // LIGHT_H
