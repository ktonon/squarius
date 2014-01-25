/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQEngine.h"
#include "Game/SQPuzzleEngine.h"


const int SQEngine::FRAMES_PER_SECOND = 30;

SQEngine::SQEngine(QWidget *parent) :
    QGLWidget(parent),
    _renderTimer(),
    _puzzleEngine(NULL),
    _height(-1),
    _width(-1)
{
    _renderTimer.setSingleShot(false);
    _renderTimer.setInterval(1000.0f / FRAMES_PER_SECOND);
    connect(&_renderTimer, SIGNAL(timeout()), SLOT(tick()));

    // TODO: replace this with real level loader
    _puzzleEngine = new SQPuzzleEngine(SQPuzzle::load(0, 0), this);
}

SQEngine::~SQEngine()
{
}

void SQEngine::initializeGL()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.15f, 0.2f, 1.0f);
}

void SQEngine::tick()
{
    _puzzleEngine->updateModelView();
    update();
}

void SQEngine::paintGL()
{

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(_puzzleEngine->projectionMatrix());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -_puzzleEngine->distanceToModelView());
    glMultMatrixf(_puzzleEngine->modelViewMatrix());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    _puzzleEngine->renderModel();
    glPopMatrix();
}

void SQEngine::resizeGL(int w, int h)
{
    _width = w;
    _height = h;
    glViewport(0, 0, _width, _height);
    _puzzleEngine->setRatio((GLfloat) w / h);
    if (shouldStartRendering())
    {
        _puzzleEngine->activate();
        _renderTimer.start();
    }
}

void SQEngine::togglePerspective()
{
    _puzzleEngine->perspectiveSwitchBegin();
}
