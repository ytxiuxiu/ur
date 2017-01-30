#include <math.h>

#include "robotthread.h"


RobotThread::RobotThread(int id, qintptr socketDescriptor, RobotServer* server, QObject* parent) :
    QThread(parent)
{
    this->id = id;
    this->socketDescriptor = socketDescriptor;
    this->server = server;
}

void RobotThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if (!socket->setSocketDescriptor(socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << id << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void RobotThread::readyRead()
{
    QString data(socket->readAll());

    qDebug() << data;

    // put data into the buffer
    this->buffer += data;

    // split info from buffer
    if (this->buffer.contains(';'))
    {
        QStringList infoList = this->buffer.split(';');
        this->buffer = infoList.last();
        infoList.removeLast();

        for (int i = 0; i < infoList.size(); i++)
        {
            qDebug() << infoList[i];
            processInfo(infoList[i]);
        }
    }
}

void RobotThread::processInfo(QString info)
{
    QStringList infoParts = info.split(':');
    QString key = infoParts[0];
    QString value = infoParts[1];

    if (key == "status")
    {
        qDebug() << id << " Received status: " << value;
        server->statusChanged(id, value.toInt());
    }
    else if (key == "actualTcp")
    {
        qDebug() << id << " Received actual TCP: " << this->str2FloatArray(value);
    }
    else if (key == "actualJoint")
    {
        float* joint = this->str2FloatArray(value);
        qDebug() << id << " Received actual joint: " << joint;
        server->actualJointChanged(rad2deg(joint[0]), rad2deg(joint[1]), rad2deg(joint[2]),
                rad2deg(joint[3]), rad2deg(joint[4]), rad2deg(joint[5]));
    }
    else if (key == "targetJoint")
    {
        qDebug() << " Target joint!";
    }
}

void RobotThread::sendTarget(float base, float shoulder, float elbow, float wrist1, float wrist2, float wrist3)
{
    QString target = "(" + QString::number(deg2rad(base)) + "," + QString::number(deg2rad(shoulder)) + "," + QString::number(deg2rad(elbow)) + "," +
            QString::number(deg2rad(wrist1)) + "," + QString::number(deg2rad(wrist2)) + "," + QString::number(deg2rad(wrist3)) + ")\n";
    socket->write(target.toUtf8());
}

float* RobotThread::str2FloatArray(QString str)
{
    QStringList floats = str.split(',');
    float* arr = new float[floats.size()];
    for (int i = 0; i < floats.size(); i++)
    {
        arr[i] = floats[i].toFloat();
    }
    return arr;
}

float RobotThread::rad2deg(float rad)
{
    return rad * 180 / M_PI;
}

float RobotThread::deg2rad(float deg)
{
    return deg * M_PI / 180;
}

void RobotThread::disconnected()
{
    qDebug() << id << " Disconnected";

    socket->deleteLater();
    exit(0);
}
