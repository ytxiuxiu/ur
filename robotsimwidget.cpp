#include <istream>

#include "robotsimwidget.h"

using namespace glm;


RobotSimWidget::RobotSimWidget(QWidget* parent) :
    QOpenGLWidget(parent)
{
    renderCount = 0;
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
    delete camera;
    camera = 0;
}

void RobotSimWidget::initializeGL()
{
    light = new Light(vec3(5000, 0, 5000), vec3(1, 1, 1));
    camera = new Camera(vec3(50, 450, 500), vec3(20, 0, 0));

    loader = new Loader();
    shader = new StaticShader();
    shader->compile();
    renderer = new Renderer(shader);

    Entity* robotBase = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-base.obj"), loader));
    entities.insert(std::pair<std::string, Entity*>("robot-0-base", robotBase));

    RawModel* xyz = ObjLoader::loadObjModel(File::readFile(":/models/xyz.obj"), loader);

    Entity* xyz0 = new Entity(xyz, vec3(0, 0, 0), vec3(0, 0, 0), 1, std::vector<vec3>{ vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1) }, true);
    entities.insert(std::pair<std::string, Entity*>("robot-0-xyz-0", xyz0));
    Entity* robot1 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-1.obj"), loader),
                               vec3(0, 86.05, 0), vec3(0, 0, 0), 1, std::vector<vec3>{ vec3(0.561, 0.694, 0.91) });
    entities.insert(std::pair<std::string, Entity*>("robot-0-1", robot1));

    Entity* xyz1 = new Entity(xyz, vec3(0, 0, 0), vec3(0, 0, 0), 1, std::vector<vec3>{ vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1) }, true);
    entities.insert(std::pair<std::string, Entity*>("robot-0-xyz-1", xyz1));
    Entity* robot2 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-2.obj"), loader));
    entities.insert(std::pair<std::string, Entity*>("robot-0-2", robot2));

    Entity* xyz2 = new Entity(xyz, vec3(0, 0, 0), vec3(0, 0, 0), 1, std::vector<vec3>{ vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1) }, true);
    entities.insert(std::pair<std::string, Entity*>("robot-0-xyz-2", xyz2));
    Entity* robot3 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-3.obj"), loader));
    entities.insert(std::pair<std::string, Entity*>("robot-0-3", robot3));


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

    std::map<std::string, Entity*>::iterator it = entities.begin();
    while (it != entities.end())
    {
        renderer->render(it->second);
        it++;
    }

    shader->stop();
}
