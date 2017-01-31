#include <istream>

#include "robotsimwidget.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader.h"

RobotSimWidget::RobotSimWidget(QWidget* parent) :
    QOpenGLWidget(parent)
{

}

RobotSimWidget::~RobotSimWidget()
{
    makeCurrent();
    loader->cleanUp();
    shader->cleanUp();
    doneCurrent();
}

void RobotSimWidget::initializeGL()
{
    loader = new Loader();
    renderer = new Renderer();
    shader = new StaticShader();

    std::vector<GLfloat> vertices = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    model = loader->loadToVao(&vertices);
}

void RobotSimWidget::resizeGL(int w, int h)
{

}

void RobotSimWidget::paintGL()
{
    renderer->prepare();
    shader->start();
    renderer->render(model);
    shader->stop();
}
