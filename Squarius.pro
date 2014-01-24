#-------------------------------------------------
#
# Project created by QtCreator 2014-01-22T19:25:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Squarius
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    GLWidget.cpp

HEADERS  += MainWindow.h \
    GLWidget.h

FORMS    += MainWindow.ui
