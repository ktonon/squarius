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
    SQEngine.cpp \
    Perspectives/SQPerspective.cpp \
    Perspectives/SQPerspective2d.cpp \
    Perspectives/SQPerspective3d.cpp \
    Perspectives/SQPerspectiveSwitcher.cpp \
    Game/SQPuzzle.cpp \
    Game/SQPuzzleEngine.cpp \
    Utilities/Matrix.cpp

HEADERS  += MainWindow.h \
    SQEngine.h \
    Perspectives/SQPerspective.h \
    Perspectives/SQPerspective2d.h \
    Perspectives/SQPerspective3d.h \
    Perspectives/SQPerspectiveSwitcher.h \
    SQPerspectives.h \
    Game/SQPuzzle.h \
    Game/SQPuzzleEngine.h \
    SQTypes.h \
    Utilities/Memory.h \
    Utilities/Matrix.h

FORMS    += MainWindow.ui
