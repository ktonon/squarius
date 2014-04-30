#-------------------------------------------------
#
# Project created by QtCreator 2014-01-22T19:25:33
#
#-------------------------------------------------

QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Squarius
TEMPLATE = app

QMAKE_INFO_PLIST = Info.plist

INCLUDEPATH += .

SOURCES += main.cpp\
    MainWindow.cpp \
    SQEngine.cpp \
    Perspectives/SQPerspective.cpp \
    Perspectives/SQPerspective2d.cpp \
    Perspectives/SQPerspective3d.cpp \
    Perspectives/SQPerspectiveSwitcher.cpp \
    Game/SQPuzzle.cpp \
    Game/SQPuzzleEngine.cpp \
    Utilities/Matrix.cpp \
    Game/SQBlock.cpp \
    Utilities/SQPrimitives.cpp \
    Utilities/SQStack.cpp \
    Gestures/SQPanGestureRecognizer.cpp

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
    Utilities/Matrix.h \
    Game/SQBlock.h \
    Utilities/SQPrimitives.h \
    SQOpenGL.h \
    Utilities/SQStack.h \
    IPerspectiveProvider.h \
    Gestures/SQPanGestureRecognizer.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    fshader.fsh \
    vshader.vsh

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    puzzles.qrc
