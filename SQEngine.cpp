/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQEngine.h"

const GLfloat SQEngine::NEAR = 10.0f;

SQEngine::SQEngine(QWidget *parent) :
    QGLWidget(parent),
    _perspective(NULL),
    _perspective2d(NULL),
    _perspective3d(NULL),
    _perspectiveSwitcher(NULL),
    _isCubeLocked(true),
    _isGesturing(false),
    _lastModelView(),
    _rotI(0.0f),
    _rotJ(0.0f),
    _rotK(0.0f),
    _isFirstRender(true),
    _offset(0.0f)
{
    _perspective2d = new SQPerspective2d(this);
    _perspective3d = new SQPerspective3d(this);
    _perspective = _perspective2d;
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
    glLoadMatrixf(_perspective->projectionMatrix());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -NEAR * 1.5f + _offset);

    applyGesturesToModelView();
    if (shouldPullViewToAxis()) pullViewToAxis();
    glMultMatrixf(_lastModelView);

    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    _perspective->renderModel();
    glPopMatrix();
}

void SQEngine::applyGesturesToModelView()
{
    glPushMatrix();
    if (_isFirstRender)
    {
        _isFirstRender = false;
        glLoadIdentity();
    }
    else
        glLoadMatrixf(_lastModelView);

    glRotatef(_rotI, _lastModelView[0], _lastModelView[4], _lastModelView[8]);
    glRotatef(_rotJ, _lastModelView[1], _lastModelView[5], _lastModelView[9]);
    glRotatef(_rotK, _lastModelView[2], _lastModelView[6], _lastModelView[10]);
    glGetFloatv(GL_MODELVIEW_MATRIX, _lastModelView);
    glPopMatrix();
    _rotI = _rotJ = _rotK = 0.0f;
}

void SQEngine::pullViewToAxis()
{
    const GLubyte DIM_A = 1, DIM_B = 2, DIM_C = 4;
    GLfloat v[3];
    GLfloat w[3];
    GLfloat a, b, c;
    GLubyte alreadyUsedDims = 0; // keep track of used dimensions, 1, 2, 4
    GLubyte useDim;
    GLfloat delta[3];
    GLfloat mag;
    GLfloat incr = 0.03;
    alreadyUsedDims = 0; // keep track of used dimensions, 1, 2, 4
    for (int d=0; d<3; d++) {
        w[0] = w[1] = w[2] = 0;
        v[0] = _lastModelView[0+d];
        v[1] = _lastModelView[4+d];
        v[2] = _lastModelView[8+d];
        a = fabs(v[0]);
        b = fabs(v[1]);
        c = fabs(v[2]);

        if (a > b && a > c) useDim = alreadyUsedDims & DIM_A ? (b > c ? (alreadyUsedDims & DIM_B ? 2 : 1) : (alreadyUsedDims & DIM_C ? 1 : 2)) : 0;
        else if (b > a && b > c) useDim = alreadyUsedDims & DIM_B ? (a > c ? (alreadyUsedDims & DIM_A ? 2 : 0) : (alreadyUsedDims & DIM_C ? 0 : 2)) : 1;
        else if (c > a && c > b) useDim = alreadyUsedDims & DIM_C ? (a > b ? (alreadyUsedDims & DIM_A ? 1 : 0) : (alreadyUsedDims & DIM_B ? 0 : 1)) : 2;

        alreadyUsedDims |= (GLubyte)pow(2, useDim);
        w[useDim] = v[useDim] > 0 ? 1 : -1;

        delta[0] = w[0] - v[0];
        delta[1] = w[1] - v[1];
        delta[2] = w[2] - v[2];
        mag = sqrt(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
        if (mag > 0) {
            if (mag < 0.03) {
                _lastModelView[0+d] = w[0];
                _lastModelView[4+d] = w[1];
                _lastModelView[8+d] = w[2];
                _perspective->updateOrientation(_lastModelView);
            } else {
                _lastModelView[0+d] = v[0] + delta[0] / mag * incr;
                _lastModelView[4+d] = v[1] + delta[1] / mag * incr;
                _lastModelView[8+d] = v[2] + delta[2] / mag * incr;
            }
        }
    }
}

void SQEngine::resizeGL(int w, int h)
{

}
