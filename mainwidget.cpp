#include <math.h>
#include <iostream>

#include "mainwidget.h"
#include "ui_mainwidget.h"


MainWidget::MainWidget(RobotServer *server, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    inited = false;

    ui->setupUi(this);

    connect(server, SIGNAL(actualJointChanged(float,float,float,float,float,float)),
            this, SLOT(changeJoint(float,float,float,float,float,float)));

    connect(ui->targetBase, SIGNAL(valueChanged(int)), this, SLOT(changeLabelTargetBase(int)));
    connect(ui->targetShoulder, SIGNAL(valueChanged(int)), this, SLOT(changeLabelTargetShoulder(int)));
    connect(ui->targetElbow, SIGNAL(valueChanged(int)), this, SLOT(changeLabelTargetElbow(int)));
    connect(ui->targetWrist1, SIGNAL(valueChanged(int)), this, SLOT(changeLabelTargetWrist1(int)));
    connect(ui->targetWrist2, SIGNAL(valueChanged(int)), this, SLOT(changeLabelTargetWrist2(int)));
    connect(ui->targetWrist3, SIGNAL(valueChanged(int)), this, SLOT(changeLabelTargetWrist3(int)));

//    connect(ui->targetBase, SIGNAL(sliderReleased()), this, SLOT(getTarget()));
//    connect(ui->targetShoulder, SIGNAL(sliderReleased()), this, SLOT(getTarget()));
//    connect(ui->targetElbow, SIGNAL(sliderReleased()), this, SLOT(getTarget()));
//    connect(ui->targetWrist1, SIGNAL(sliderReleased()), this, SLOT(getTarget()));
//    connect(ui->targetWrist2, SIGNAL(sliderReleased()), this, SLOT(getTarget()));
//    connect(ui->targetWrist3, SIGNAL(sliderReleased()), this, SLOT(getTarget()));

    connect(this, SIGNAL(sendTarget(int,float,float,float,float,float,float)),
            server, SLOT(sendTarget(int,float,float,float,float,float,float)));
    connect(server, SIGNAL(statusChanged(int,int)), this, SLOT(changeStatus(int,int)));

    robotSimWidget = new RobotSimWidget();
    ui->verticalLayout->addWidget(robotSimWidget);

    paintTimer = new QTimer(this);
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(updateRobotSimWidget()));

    paintTimer->start(1000.0f / FPS);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::changeJoint(float base, float shoulder, float elbow, float wrist1, float wrist2, float wrist3)
{
    ui->actualBase->setValue(base);
    ui->actualShoulder->setValue(shoulder);
    ui->actualElbow->setValue(elbow);
    ui->actualWrist1->setValue(wrist1);
    ui->actualWrist2->setValue(wrist2);
    ui->actualWrist3->setValue(wrist3);

    if (!inited) {
        ui->targetBase->setValue(ui->actualBase->value());
        ui->targetShoulder->setValue(ui->actualShoulder->value());
        ui->targetElbow->setValue(ui->actualElbow->value());
        ui->targetWrist1->setValue(ui->actualWrist1->value());
        ui->targetWrist2->setValue(ui->actualWrist2->value());
        ui->targetWrist3->setValue(ui->actualWrist3->value());
        inited = true;
    }

    ui->labelActualBase->setText(float2DegStr(base));
    ui->labelActualShoulder->setText(float2DegStr(shoulder));
    ui->labelActualElbow->setText(float2DegStr(elbow));
    ui->labelActualWrist1->setText(float2DegStr(wrist1));
    ui->labelActualWrist2->setText(float2DegStr(wrist2));
    ui->labelActualWrist3->setText(float2DegStr(wrist3));
}

QString MainWidget::float2DegStr(float value)
{
    char buff[10];
    snprintf(buff, sizeof(buff), "%+.2f°", value);
    return QString(buff);
}

void MainWidget::changeLabelTargetBase(int base)
{
    ui->labelTargetBase->setText(float2DegStr(base));
    Entity *robot1 = robotSimWidget->getEntities()->at("robot-0-1");
    robot1->setRotation(vec3(robot1->getRotation().x, base, robot1->getRotation().z));

    t1 = Maths::createDhTransformation(152, base, 0, 90);
    vec3 p1 = Maths::getPosition(t1);
    vec3 r1 = Maths::getRotation(t1);

    Entity *robot2 = robotSimWidget->getEntities()->at("robot-0-2");
    robot2->setPosition(p1);
    robot2->setRotation(r1);
    Entity *xyz1 = robotSimWidget->getEntities()->at("robot-0-xyz-1");
    xyz1->setPosition(p1);
    xyz1->setRotation(r1);

}

void MainWidget::changeLabelTargetShoulder(int shoulder)
{
    ui->labelTargetShoulder->setText(float2DegStr(shoulder));

    mat4 r1r = rotate(mat4(1), radians(1.0f * shoulder), vec3(0, 0, 1)) * t1;
    vec3 rotation = Maths::getRotation(r1r);
    Entity *robot2 = robotSimWidget->getEntities()->at("robot-0-2");
    robot2->setRotation(rotation);

    t2 = Maths::createDhTransformation(-120, shoulder, -244, 0) * t1;
    vec3 p2 = Maths::getPosition(t2);
    vec3 r2 = Maths::getRotation(t2);

    Entity *robot3 = robotSimWidget->getEntities()->at("robot-0-3");
    robot3->setPosition(p2);
    robot3->setRotation(r2);
    Entity *xyz2 = robotSimWidget->getEntities()->at("robot-0-xyz-2");
    xyz2->setPosition(p2);
    xyz2->setRotation(r2);


}

void MainWidget::changeLabelTargetElbow(int elbow)
{
    ui->labelTargetElbow->setText(float2DegStr(elbow));

    mat4 r2r = rotate(mat4(1), radians(1.0f * elbow), vec3(0, 0, 1)) * t1;
    vec3 rotation = Maths::getRotation(r2r);
    Entity *robot3 = robotSimWidget->getEntities()->at("robot-0-3");
    robot3->setRotation(rotation);
}

void MainWidget::changeLabelTargetWrist1(int wrist1)
{
    ui->labelTargetWrist1->setText(float2DegStr(wrist1));
}

void MainWidget::changeLabelTargetWrist2(int wrist2)
{
    ui->labelTargetWrist2->setText(float2DegStr(wrist2));
}

void MainWidget::changeLabelTargetWrist3(int wrist3)
{
    ui->labelTargetWrist3->setText(float2DegStr(wrist3));
}

void MainWidget::getTarget()
{
    ui->targetBase->setDisabled(true);
    ui->targetShoulder->setDisabled(true);
    ui->targetElbow->setDisabled(true);
    ui->targetWrist1->setDisabled(true);
    ui->targetWrist2->setDisabled(true);
    ui->targetWrist3->setDisabled(true);

    sendTarget(0, ui->targetBase->value(), ui->targetShoulder->value(), ui->targetElbow->value(),
               ui->targetWrist1->value(), ui->targetWrist2->value(), ui->targetWrist3->value());
}

void MainWidget::changeStatus(int robot, int status)
{
    QString statusStr;
    switch (status)
    {
    case 0:
        statusStr = "IDLE";
        break;
    case 1:
        statusStr = "MOVING";
        break;
    default:
        statusStr = "OFFLINE";
        break;
    }

    if (robot == 0)
    {
        ui->labelRobot1Status->setText(statusStr);

        if (status == 0)
        {
            ui->targetBase->setDisabled(false);
            ui->targetShoulder->setDisabled(false);
            ui->targetElbow->setDisabled(false);
            ui->targetWrist1->setDisabled(false);
            ui->targetWrist2->setDisabled(false);
            ui->targetWrist3->setDisabled(false);
        }
    }
}

void MainWidget::updateRobotSimWidget()
{
//    int position = robotSimWidget->getRenderCount() % (FPS * 10);
//    float deg = 360.0f * position / (FPS * 10);
//    float x = std::sin(glm::radians(deg)) * 250;
//    float z = std::cos(glm::radians(deg)) * 250;

//    Camera *camera = robotSimWidget->getCamera();

//    camera->setPosition(glm::vec3(x, 450, z));
//    camera->setRotation(vec3(40, -deg, 0));

    robotSimWidget->update();
    robotSimWidget->setRenderCount(robotSimWidget->getRenderCount() + 1);
}
