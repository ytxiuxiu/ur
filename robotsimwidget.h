#ifndef ROBOTSIMWIDGET_H
#define ROBOTSIMWIDGET_H

#include <QtWidgets>


class RobotSimWidget : public QOpenGLWidget
{
public:
    RobotSimWidget(QWidget* parent = 0);
    ~RobotSimWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vertexShader;
    QOpenGLShader* fragmentShader;
};

#endif // ROBOTSIMWIDGET_H
