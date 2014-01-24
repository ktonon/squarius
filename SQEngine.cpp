/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQEngine.h"

SQEngine::SQEngine(QWidget *parent) :
    QGLWidget(parent),
    _perspective(NULL),
    _perspective2d(NULL),
    _perspective3d(NULL),
    _perspectiveSwitcher(NULL)
{
}

SQEngine::~SQEngine()
{

}

void SQEngine::initializeGL()
{
    glClearColor(0, 0, 1, 1);
}

void SQEngine::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void SQEngine::resizeGL(int w, int h)
{

}