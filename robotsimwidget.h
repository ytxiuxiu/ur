#ifndef ROBOTSIMWIDGET_H
#define ROBOTSIMWIDGET_H

#include <vector>
#include <QtWidgets>
#include <glm/glm.hpp>

#include "rawmodel.h"
#include "loader.h"
#include "renderer.h"
#include "staticshader.h"
#include "file.h"
#include "light.h"
#include "objloader.h"


class RobotSimWidget : public QOpenGLWidget
{
public:
    RobotSimWidget(QWidget* parent = 0);
    ~RobotSimWidget();
    Entity *getEntity() { return entity; }
    Camera *getCamera() { return camera; }

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
    Entity *entity;
    Camera *camera;
    Light *light;
    ObjLoader *objLoader;

};

#endif // ROBOTSIMWIDGET_H
