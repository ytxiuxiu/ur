#include "robotserver.h"
#include "robotthread.h"

RobotServer::RobotServer(QObject* parent) :
    QTcpServer(parent)
{

}

RobotServer::~RobotServer()
{
    for (int i = 0; i < threads.size(); i++) {
        delete threads[i];
    }
}

void RobotServer::startServer()
{
    int port = 55056;

    if (!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }
}

// This function is called by QTcpServer when a new connection is available.
void RobotServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << "Robot "<< threads.size() << " Connecting...";

    // Every new connection will be run in a newly created thread
    RobotThread* thread = new RobotThread(threads.size(), socketDescriptor, this);
    threads.append(thread);

    // connect signal/slot
    // once a thread is not needed, it will be deleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

void RobotServer::sendTarget(int robot, float base, float shoulder, float elbow, float wrist1, float wrist2, float wrist3)
{
    threads[robot]->sendTarget(base, shoulder, elbow, wrist1, wrist2, wrist3);
}
