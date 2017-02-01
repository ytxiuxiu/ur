#include <istream>

#include "robotsimwidget.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader.h"

using namespace glm;


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
    delete camera;
    camera = 0;
}

void RobotSimWidget::initializeGL()
{
    loader = new Loader();
    shader = new StaticShader();
    shader->compile();
    renderer = new Renderer(shader);

    std::vector<GLfloat> vertices = {
        -0.5f,0.5f,-0.5f,
                        -0.5f,-0.5f,-0.5f,
                        0.5f,-0.5f,-0.5f,
                        0.5f,0.5f,-0.5f,

                        -0.5f,0.5f,0.5f,
                        -0.5f,-0.5f,0.5f,
                        0.5f,-0.5f,0.5f,
                        0.5f,0.5f,0.5f,

                        0.5f,0.5f,-0.5f,
                        0.5f,-0.5f,-0.5f,
                        0.5f,-0.5f,0.5f,
                        0.5f,0.5f,0.5f,

                        -0.5f,0.5f,-0.5f,
                        -0.5f,-0.5f,-0.5f,
                        -0.5f,-0.5f,0.5f,
                        -0.5f,0.5f,0.5f,

                        -0.5f,0.5f,0.5f,
                        -0.5f,0.5f,-0.5f,
                        0.5f,0.5f,-0.5f,
                        0.5f,0.5f,0.5f,

                        -0.5f,-0.5f,0.5f,
                        -0.5f,-0.5f,-0.5f,
                        0.5f,-0.5f,-0.5f,
                        0.5f,-0.5f,0.5f
    };

    std::vector<GLuint> indices = {
        0,1,3,
                        3,1,2,
                        4,5,7,
                        7,5,6,
                        8,9,11,
                        11,9,10,
                        12,13,15,
                        15,13,14,
                        16,17,19,
                        19,17,18,
                        20,21,23,
                        23,21,22
    };

    model = loader->loadToVao(&vertices, &indices);

    vec3 location(-1, 0, -3);
    vec3 rotation(0, 0, 0);

    entity = new Entity(model, location, rotation, 1);

    camera = new Camera(vec3(0, 0, 0), vec3(0, 0, 0));
}

void RobotSimWidget::resizeGL(int w, int h)
{

}

void RobotSimWidget::paintGL()
{
    qDebug() << "paint";
    renderer->prepare();
    shader->start();
    shader->loadView(camera);
    renderer->render(entity, shader);
    shader->stop();
}
