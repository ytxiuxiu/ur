#include "robotsimwidget.h"

RobotSimWidget::RobotSimWidget(QWidget* parent) :
    QOpenGLWidget(parent)
{

}

RobotSimWidget::~RobotSimWidget()
{
//    delete this->vertexShader;
}

void RobotSimWidget::initializeGL()
{
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    this->vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    this->vertexShader->compileSourceFile(":/glsl/vertex.glsl");
    this->fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    this->fragmentShader->compileSourceFile(":/glsl/fragment.glsl");

    this->program = new QOpenGLShaderProgram;
    this->program->addShader(this->vertexShader);
    this->program->addShader(this->fragmentShader);
    this->program->link();
    this->program->bind();


}

void RobotSimWidget::resizeGL(int w, int h)
{

}

void RobotSimWidget::paintGL()
{
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
}
