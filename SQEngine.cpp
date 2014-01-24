/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQEngine.h"

SQEngine::SQEngine(QWidget *parent) :
    QGLWidget(parent)
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
