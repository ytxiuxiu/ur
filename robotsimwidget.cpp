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
    delete kinematicChain;
    kinematicChain = 0;
}

void RobotSimWidget::initializeGL()
{
    light = new Light(vec3(5000, 0, 5000), vec3(1, 1, 1));
    camera = new Camera(vec3(50, 650, 800), vec3(20, 0, 0));

    kinematicChain = new KinematicChain();

    loader = new Loader();
    Entity* robot2 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-2.obj"), loader));
    Entity* robot3 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-3.obj"), loader));
    Entity* robot4 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-4.obj"), loader));
    Entity* robot5 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-5.obj"), loader));
    Entity* robot6 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-6.obj"), loader));

    kinematicChain->addLink(new KinematicLink(robot2, 0, 152, 0, 90));
    kinematicChain->addLink(new KinematicLink(robot3, -90, -120, -244, 0));
    kinematicChain->addLink(new KinematicLink(robot4, 0, 93, -213, 0));
    kinematicChain->addLink(new KinematicLink(robot5, -90, -83, 0, 90));
    kinematicChain->addLink(new KinematicLink(robot6, 0, 82, 0, 0));
    kinematicChain->update();

    shader = new StaticShader();
    shader->compile();
    renderer = new Renderer(shader);

    Entity* robotBase = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-base.obj"), loader));
    entities.insert(std::pair<std::string, Entity*>("robot-0-base", robotBase));

//    RawModel* xyz = ObjLoader::loadObjModel(File::readFile(":/models/xyz.obj"), loader);

//    Entity* xyz0 = new Entity(xyz, vec3(0, 0, 0), vec3(0, 0, 0), 1, std::vector<vec3>{ vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1) }, true);
//    entities.insert(std::pair<std::string, Entity*>("robot-0-xyz-0", xyz0));
    Entity* robot1 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-1.obj"), loader),
                               vec3(0, 86.05, 0), vec3(0, 0, 0), 1, std::vector<vec3>{ vec3(0.561, 0.694, 0.91) });
    entities.insert(std::pair<std::string, Entity*>("robot-0-1", robot1));


//    Entity* xyz2 = new Entity(xyz, vec3(0, 0, 0), vec3(0, 0, 0), 1, std::vector<vec3>{ vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1) }, true);
//    entities.insert(std::pair<std::string, Entity*>("robot-0-xyz-2", xyz2));
//    Entity* robot3 = new Entity(ObjLoader::loadObjModel(File::readFile(":/models/robot-3.obj"), loader));
//    entities.insert(std::pair<std::string, Entity*>("robot-0-3", robot3));


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
    for (unsigned long i = 0; i < kinematicChain->getLinks().size(); i++)
    {
        vec3 p = kinematicChain->getLinks()[i]->getEntity()->getPosition();

        renderer->render(kinematicChain->getLinks()[i]->getEntity());
    }

    shader->stop();
}
