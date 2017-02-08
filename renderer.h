#ifndef RENDERER_H
#define RENDERER_H

#include <QtWidgets>
#include <glm/glm.hpp>
#include <math.h>

#include "staticshader.h"
#include "entity.h"
#include "maths.h"

#define SCENE_WIDTH 549.0f
#define SCENE_HEIGHT 291.0f
#define FOV 70.0f
#define NEAR_PLANE 0.1f
#define FAR_PLANE 100000.0f

using namespace glm;


class Renderer
{
public:
    Renderer(StaticShader *shader);
    void prepare();
    void render(Entity* entity);

private:
    mat4 projection;
    StaticShader *shader;
};

#endif // RENDERER_H
