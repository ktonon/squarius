/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQEngine.h"
#include "Game/SQPuzzleEngine.h"


SQEngine::SQEngine(QWidget *parent) :
    QGLWidget(parent)
{
    // TODO: replace this with real level loader
    _puzzleEngine = new SQPuzzleEngine(SQPuzzle::load(0, 0), this);
    QTimer* timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->setInterval(50);
    connect(timer, SIGNAL(timeout()), _puzzleEngine, SLOT(updateModelView()));
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
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(_puzzleEngine->projectionMatrix());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -_puzzleEngine->distanceToModelView());
    glMultMatrixf(_puzzleEngine->modelViewMatrix());

    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    _puzzleEngine->renderModel();
    glPopMatrix();
}

void SQEngine::resizeGL(int w, int h)
{

}
