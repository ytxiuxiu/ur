#include <QApplication>
#include <QtGui>

#include "mainwidget.h"
#include "robotserver.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RobotServer server;
    server.startServer();

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    MainWidget w(&server);
    w.show();

    return a.exec();
}
