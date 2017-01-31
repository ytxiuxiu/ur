#ifndef RENDERER_H
#define RENDERER_H

#include <QtWidgets>

#include "rawmodel.h"


class Renderer
{
public:
    Renderer();
    void prepare();
    void render(RawModel* model);
};

#endif // RENDERER_H
