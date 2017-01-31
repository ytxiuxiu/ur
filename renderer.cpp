#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::prepare()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Renderer::render(RawModel *model)
{
    glBindVertexArray(model->getVaoId());
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLES, 0, model->getIndices()->size());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
