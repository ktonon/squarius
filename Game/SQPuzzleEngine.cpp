/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPuzzleEngine.h"
#include "Utilities/Memory.h"
#include "Utilities/SQStack.h"
#include <math.h>

SQPuzzleEngine::SQPuzzleEngine(SQPuzzle::SP puzzle, QObject *parent) :
    QObject(parent),
    _puzzle(puzzle),
    _perspective(NULL),
    _perspective2d(NULL),
    _perspective3d(NULL),
    _perspectiveSwitcher(NULL),
    _isActive(false),
    _isCubeLocked(true),
    _isGesturing(false),
    _rotI(0.0f),
    _rotJ(0.0f),
    _rotK(0.0f),
    _isFirstRender(true),
    _offset(puzzle->maxDimension() / 2.0f)
{
    int n = puzzle->maxDimension();
    _perspective2d = new SQPerspective2d(n, this);
    _perspective3d = new SQPerspective3d(n, this);
    _perspective = _perspective2d;
}

SQPuzzleEngine::~SQPuzzleEngine()
{
}

bool SQPuzzleEngine::panGesture(SQPanGesture *gesture)
{
    static const float bound = 10.0f;
    if (gesture->state() == Qt::GestureStarted)
        _isGesturing = true;
    if (gesture->state() == Qt::GestureFinished || gesture->state() == Qt::GestureCanceled)
        _isGesturing = false;
    if (_perspective == _perspective3d)
    {
        _rotI = fmaxf(fminf(gesture->delta().y(), bound), -bound);
        _rotJ = fmaxf(fminf(gesture->delta().x(), bound), -bound);
    }
    return true;
}

bool SQPuzzleEngine::pinchGesture(QPinchGesture *gesture)
{
    if (gesture->state() == Qt::GestureUpdated && _perspective == _perspective3d)
    {
//        _rotK = (gesture->lastRotationAngle() - gesture->rotationAngle()) * 8;
    }
    if (gesture->state() == Qt::GestureFinished)
    {
//        if ((_perspective == _perspective2d && gesture->scaleFactor() < 1) ||
//            (_perspective == _perspective3d && gesture->scaleFactor() > 1))
//            perspectiveSwitchBegin();
    }
    return true;
}

bool SQPuzzleEngine::tapGesture(QTapGesture *)
{
    return false;
}

void SQPuzzleEngine::renderModel()
{
    _puzzle->renderCells();
}

void SQPuzzleEngine::perspectiveSwitchBegin()
{
    if (!isPerspectiveSwitching())
    {
        _perspectiveSwitcher = new SQPerspectiveSwitcher(
                    _perspective,
                    otherPerspective(),
                    SQPerspectiveSwitcher::DEFAULT_DURATION,
                    this);
        connect(_perspectiveSwitcher, SIGNAL(deactivated()), this, SLOT(perspectiveSwitchEnd()));
        _perspective = _perspectiveSwitcher;
        _perspectiveSwitcher->activate();
    }
}

void SQPuzzleEngine::perspectiveSwitchEnd()
{
    _perspective = _perspectiveSwitcher->endPerspective();
    SafeDeleteLater(_perspectiveSwitcher);
    emit perspectedSwitchEnded();
}

void SQPuzzleEngine::updateModelView()
{
    applyGesturesToModelView();
    if (shouldPullViewToAxis()) pullViewToAxis();
}

void SQPuzzleEngine::applyGesturesToModelView()
{
    static const float DISTANCE = 20;
    if (_isFirstRender)
    {
        _isFirstRender = false;
        SQStack::instance()
                ->loadIdentity()
                ->translate(0, 0, - DISTANCE);
    }

    if (shouldPullViewToAxis())
        _rotI = _rotJ = _rotK = 0.0f;

    SQStack::instance()
            ->translate(0, 0, DISTANCE)
            ->rotate(_rotI, QVector3D(1,0,0))
            ->rotate(_rotJ, QVector3D(0,1,0))
            ->rotate(_rotK, QVector3D(0,0,1))
            ->translate(0, 0, - DISTANCE)
            ;
}

void SQPuzzleEngine::pullViewToAxis()
{
    const GLubyte DIM_A = 1, DIM_B = 2, DIM_C = 4;
    QVector4D v;
    QVector4D w;
    GLfloat a, b, c;
    GLubyte alreadyUsedDims = 0; // keep track of used dimensions, 1, 2, 4
    GLubyte useDim;
    QVector4D delta;
    GLfloat mag;
    GLfloat incr = _perspective == _perspective3d ? 0.3 : 0.3;
    alreadyUsedDims = 0; // keep track of used dimensions, 1, 2, 4
    QMatrix4x4 modelView = SQStack::instance()->modelViewMatrix();

    // The largest absolute component of v (a model view axis vector) is the
    // vector that is closest to one of the world view axis vectors. First
    // we sort the dimensions by absolute magnitude.
    QList<int> dimOrder;
    float maxMag = 0.0f;
    for (int d=0; d<3; d++)
    {
        v = modelView.column(d);
        a = fabs(v.x());
        b = fabs(v.y());
        c = fabs(v.z());

        // Use the next largest available dimension
        if (a > b && a > c) useDim = alreadyUsedDims & DIM_A ? (b > c ? (alreadyUsedDims & DIM_B ? 2 : 1) : (alreadyUsedDims & DIM_C ? 1 : 2)) : 0;
        else if (b > a && b > c) useDim = alreadyUsedDims & DIM_B ? (a > c ? (alreadyUsedDims & DIM_A ? 2 : 0) : (alreadyUsedDims & DIM_C ? 0 : 2)) : 1;
        else if (c > a && c > b) useDim = alreadyUsedDims & DIM_C ? (a > b ? (alreadyUsedDims & DIM_A ? 1 : 0) : (alreadyUsedDims & DIM_B ? 0 : 1)) : 2;

        // Flag the dimension as being used
        alreadyUsedDims |= (GLubyte)pow(2, useDim);

        dimOrder << useDim;
        w[useDim] = v[useDim] > 0 ? 1 : -1;
        delta = w - v;
        mag = sqrt(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
        if (mag > maxMag) maxMag = mag;
    }

    for (int d=0; d<3; d++)
    {
        w = QVector4D(); // An axis aligned unit vector (i, j, or k)
        v = modelView.column(d);
        useDim = dimOrder.at(d);

        w[useDim] = v[useDim] > 0 ? 1 : -1;

        delta = w - v;
        mag = sqrt(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
        if (mag > 0)
            modelView.setColumn(d,
                                maxMag <= incr
                                ? w
                                : v + delta / mag * incr * mag / maxMag);
    }
    SQStack::instance()->replace(modelView);
}
