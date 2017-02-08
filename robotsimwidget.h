#ifndef ROBOTSIMWIDGET_H
#define ROBOTSIMWIDGET_H

#include <map>
#include <QtWidgets>
#include <glm/glm.hpp>

#include "rawmodel.h"
#include "loader.h"
#include "renderer.h"
#include "staticshader.h"
#include "file.h"
#include "light.h"
#include "objloader.h"
#include "kinematicchain.h"

#define FPS 30


class RobotSimWidget : public QOpenGLWidget
{
public:
    RobotSimWidget(QWidget* parent = 0);
    ~RobotSimWidget();
    std::map<std::string, Entity*> *getEntities() { return &entities; }
    KinematicChain* getKinematicChain() { return kinematicChain; }
    Camera *getCamera() { return camera; }
    int getRenderCount() { return renderCount; }
    void setRenderCount(int renderCount) { this->renderCount = renderCount; }

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
//    QOpenGLShaderProgram* program;
//    QOpenGLShader* vertexShader;
//    QOpenGLShader* fragmentShader;
//    QString readFile(QString filename);
//    void loadObj(QString filename, std::vector<glm::vec3>* vertices, std::vector<glm::vec2>* textures, std::vector<glm::vec3>* normals);
//    std::vector<glm::vec3>* vertexBase;

    Loader *loader;
    RawModel *model;
    Renderer *renderer;
    StaticShader *shader;
    std::map<std::string, Entity*> entities;
    Camera *camera;
    Light *light;
    ObjLoader *objLoader;
    long renderCount;
    KinematicChain *kinematicChain;

};

#endif // ROBOTSIMWIDGET_H
