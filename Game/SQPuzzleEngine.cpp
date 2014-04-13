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

SQPuzzleEngine::SQPuzzleEngine(SQPuzzle::SP puzzle, QObject *parent) :
    QObject(parent),
    _puzzle(puzzle),
    _perspective(NULL),
    _perspective2d(NULL),
    _perspective3d(NULL),
    _perspectiveSwitcher(NULL),
    _isActive(false),
    _isCubeLocked(false), // TODO: change to true
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
    if (_isFirstRender)
    {
        _isFirstRender = false;
        SQStack::instance()
                ->loadIdentity()
                ->translate(0, 0, -20);
    }

    if (shouldPullViewToAxis())
    {
        _rotI = _rotJ = _rotK = 0.0f;
    }
    else
    {
        _rotI = 1.57f;
        _rotJ = 1.27f;
        _rotK = 1.13f;
    }

    SQStack::instance()
            ->rotate(_rotI, QVector3D(1,0,0))
            ->rotate(_rotJ, QVector3D(0,1,0))
            ->rotate(_rotK, QVector3D(0,0,1));
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
    GLfloat incr = 0.03;
    alreadyUsedDims = 0; // keep track of used dimensions, 1, 2, 4
    QMatrix4x4 modelView = SQStack::instance()->modelViewMatrix();
    for (int d=0; d<3; d++)
    {
        w = QVector4D();
        v = modelView.column(d);
        a = fabs(v.x());
        b = fabs(v.y());
        c = fabs(v.z());

        if (a > b && a > c) useDim = alreadyUsedDims & DIM_A ? (b > c ? (alreadyUsedDims & DIM_B ? 2 : 1) : (alreadyUsedDims & DIM_C ? 1 : 2)) : 0;
        else if (b > a && b > c) useDim = alreadyUsedDims & DIM_B ? (a > c ? (alreadyUsedDims & DIM_A ? 2 : 0) : (alreadyUsedDims & DIM_C ? 0 : 2)) : 1;
        else if (c > a && c > b) useDim = alreadyUsedDims & DIM_C ? (a > b ? (alreadyUsedDims & DIM_A ? 1 : 0) : (alreadyUsedDims & DIM_B ? 0 : 1)) : 2;

        alreadyUsedDims |= (GLubyte)pow(2, useDim);

        switch(useDim)
        {
        case 0: w.setX(v.x() > 0 ? 1 : -1); break;
        case 1: w.setY(v.y() > 0 ? 1 : -1); break;
        case 2: w.setZ(v.z() > 0 ? 1 : -1); break;
        }

        delta = w - v;
        mag = sqrt(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
        if (mag > 0)
            modelView.setColumn(d,
                                mag < 0.03
                                ? w
                                : v + delta / mag * incr);
    }
    SQStack::instance()->replace(modelView);
}
