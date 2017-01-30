#ifndef ROBOTTHREAD_H
#define ROBOTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

#include "robotserver.h"


class RobotThread : public QThread
{
    Q_OBJECT
public:
    explicit RobotThread(int id, qintptr socketDescriptor, RobotServer* server, QObject* parent = 0);
    void run();
    void sendTarget(float base, float shoulder, float elbow, float wrist1, float wrist2, float wrist3);

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    RobotServer* server;
    QTcpSocket* socket;
    int id;
    qintptr socketDescriptor;
    QString buffer;

    void processInfo(QString info);
    float* str2FloatArray(QString str);
    float rad2deg(float rad);
    float deg2rad(float deg);
};

#endif // ROBOTTHREAD_H
