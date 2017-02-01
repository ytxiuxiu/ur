#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::prepare()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Renderer::render(Entity *entity, StaticShader *shader)
{
    RawModel *model = entity->getModel();
    glBindVertexArray(model->getVaoId());
    glEnableVertexAttribArray(0);
    glm::mat4 transformation = Maths::createTransformation(entity->getPoistion(), entity->getRotation(), entity->getScale());
    shader->loadTransformation(transformation);
    glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLES, 0, model->getIndices()->size());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
