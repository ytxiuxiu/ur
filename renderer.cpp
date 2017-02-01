#include "renderer.h"

Renderer::Renderer(StaticShader *shader)
{
    projection = perspective(radians(FOV), SCENE_WIDTH / SCENE_HEIGHT, NEAR_PLANE, FAR_PLANE);
    shader->start();
    shader->loadProjection(projection);
    shader->stop();
}

void Renderer::prepare()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.93f, 0.93f, 0.93f, 0.0f);
}

void Renderer::render(Entity *entity, StaticShader *shader)
{
    RawModel *model = entity->getModel();
    glBindVertexArray(model->getVaoId());
    glEnableVertexAttribArray(0);
    mat4 transformation = Maths::createTransformation(entity->getPoistion(), entity->getRotation(), entity->getScale());
    shader->loadTransformation(transformation);
    glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLES, 0, model->getIndices()->size());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
