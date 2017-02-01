#ifndef RENDERER_H
#define RENDERER_H

#include <QtWidgets>
#include <glm/glm.hpp>

#include "staticshader.h"
#include "entity.h"
#include "maths.h"


class Renderer
{
public:
    Renderer();
    void prepare();
    void render(Entity* entity, StaticShader *shader);
};

#endif // RENDERER_H
