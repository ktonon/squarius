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
    Gestures/SQPanGestureRecognizer.cpp \
    Game/SQWave.cpp \
    Game/SQSwarm.cpp \
    Game/SQTower.cpp \
    Game/SQCrawler.cpp \
    Menus/SQMainMenu.cpp \
    Menus/SQWorldMenu.cpp \
    Menus/SQLevelMenu.cpp \
    Menus/SQButtonGrid.cpp \
    Menus/SQButton.cpp

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
    Gestures/SQPanGestureRecognizer.h \
    Game/SQWave.h \
    Game/SQSwarm.h \
    Game/SQTower.h \
    Game/SQCrawler.h \
    Menus/SQMainMenu.h \
    Menus/SQWorldMenu.h \
    Menus/SQLevelMenu.h \
    Menus/SQButtonGrid.h \
    Menus/SQButton.h

FORMS    += MainWindow.ui \
    Menus/SQMainMenu.ui \
    Menus/SQWorldMenu.ui \
    Menus/SQLevelMenu.ui \
    Menus/SQButtonGrid.ui \
    Menus/SQButton.ui

OTHER_FILES += \
    fshader.fsh \
    vshader.vsh \
    puzzles/0000000000000000-00.xml \
    puzzles/0000000000000000-01.xml \
    puzzles/0000000000000000-02.xml

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    puzzles.qrc
