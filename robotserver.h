#ifndef ROBOTSERVER_H
#define ROBOTSERVER_H

#include <QTcpServer>

extern class RobotThread;


class RobotServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit RobotServer(QObject* parent = 0);
    ~RobotServer();
    void startServer();

signals:
    void actualJointChanged(float base, float shoulder, float elbow, float wrist1, float wrist2, float wrist3);
    void statusChanged(int robot, int status);

public slots:
    void sendTarget(int robot, float base, float shoulder, float elbow, float wrist1, float wrist2, float wrist3);

protected:
    QVector<RobotThread*> threads;
    void incomingConnection(qintptr socketDescriptor);

};

#endif // ROBOTSERVER_H
