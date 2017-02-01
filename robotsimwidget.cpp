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

    delete loader;
    loader = 0;
    delete renderer;
    renderer = 0;
    delete shader;
    shader = 0;
    delete model;
    model = 0;
    delete entity;
    entity = 0;
}

void RobotSimWidget::initializeGL()
{
    loader = new Loader();
    renderer = new Renderer();
    shader = new StaticShader();
    shader->compile();

    std::vector<GLfloat> vertices = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
//        -0.5f, 0.5f, 0.0f
    };

    std::vector<GLuint> indices = {
        0, 1, 3,
        3, 1, 2
    };

    model = loader->loadToVao(&vertices, &indices);

    glm::vec3 location(-1, 0, 0);
    glm::vec3 rotation(0, 0, 0);

    entity = new Entity(model, location, rotation, 1);
}

void RobotSimWidget::resizeGL(int w, int h)
{

}

void RobotSimWidget::paintGL()
{
    qDebug() << "paint";
    renderer->prepare();
    shader->start();
    renderer->render(entity, shader);
    shader->stop();
}
