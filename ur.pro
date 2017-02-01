#-------------------------------------------------
#
# Project created by QtCreator 2017-01-26T17:19:28
#
#-------------------------------------------------

QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ur
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwidget.cpp \
    robotsimwidget.cpp \
    robotthread.cpp \
    robotserver.cpp \
    rawmodel.cpp \
    loader.cpp \
    renderer.cpp \
    shaderprogram.cpp \
    staticshader.cpp \
    maths.cpp \
    entity.cpp \
    camera.cpp

HEADERS  += mainwidget.h \
    robotsimwidget.h \
    robotserver.h \
    robotthread.h \
    tinyobjloader.h \
    rawmodel.h \
    loader.h \
    renderer.h \
    shaderprogram.h \
    staticshader.h \
    maths.h \
    entity.h \
    camera.h

FORMS    += mainwidget.ui

RESOURCES += \
    ur3.qrc

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include


