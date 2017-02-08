#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <math.h>
#include <glm/glm.hpp>

#include "robotserver.h"
#include "robotsimwidget.h"
#include "maths.h"

using namespace glm;


namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(RobotServer *server, QWidget *parent = 0);
    ~MainWidget();

signals:
    void sendTarget(int robot, float base, float shoulder, float elbow, float wrist1, float wrist2, float wrist3);

public slots:
    void changeJoint(float base, float shoulder, float elbow, float wrist1, float wrist2, float wrist3);
    void changeLabelTargetBase(int base);
    void changeLabelTargetShoulder(int shoulder);
    void changeLabelTargetElbow(int elbow);
    void changeLabelTargetWrist1(int wrist1);
    void changeLabelTargetWrist2(int wrist2);
    void changeLabelTargetWrist3(int wrist3);
    void getTarget();
    void changeStatus(int robot, int status);
    void updateRobotSimWidget();

private:
    Ui::MainWidget *ui;
    QTimer *paintTimer;
    RobotSimWidget *robotSimWidget;
    QString float2DegStr(float value);
    bool inited;

};

#endif // MAINWIDGET_H
