#include "renderer.h"

Renderer::Renderer(StaticShader *shader)
{
    this->shader = shader;
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

void Renderer::render(Entity *entity)
{
    RawModel *model = entity->getModel();

    glBindVertexArray(model->getVaoId());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mat4 transformation = Maths::createTransformation(entity->getPoistion(), entity->getRotation(), entity->getScale());
    shader->loadTransformation(transformation);
    shader->loadIsLight(entity->getIsLight());

//    glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
    GLuint offset = 0;
    for (unsigned long i = 0; i < model->getShapeSizes().size(); i++)
    {
        if (entity->getColours().size() == 1)
        {
            shader->loadColour(entity->getColours()[0]);
        }
        else
        {
            shader->loadColour(entity->getColours()[i]);
        }
        GLuint size = model->getShapeSizes()[i];
        glDrawArrays(GL_TRIANGLES, offset, size);
        offset += size;
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);
}
