#include <istream>

#include "robotsimwidget.h"

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

    model = ObjLoader::loadObjModel(File::readFile(":/models/base.obj"), loader);
    entity = new Entity(model, vec3(0, 0, 0), vec3(45, 45, 45), 1);
    light = new Light(vec3(500, 500, 500), vec3(1, 1, 1));
    camera = new Camera(vec3(0, 0, 200), vec3(0, 0, 0));
}

void RobotSimWidget::resizeGL(int w, int h)
{

}

void RobotSimWidget::paintGL()
{
    renderer->prepare();
    shader->start();
    shader->loadView(camera);
    shader->loadLight(light);
    renderer->render(entity, shader);
    shader->stop();
}
