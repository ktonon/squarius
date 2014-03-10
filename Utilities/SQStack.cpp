/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQStack.h"
#include <math.h>

SQStack *SQStack::_instance = NULL;
qreal SQStack::PI = 3.14159265359;
const QMatrix4x4 SQStack::IDENTITY(1, 0, 0, 0,
                                   0, 1, 0, 0,
                                   0, 0, 1, 0,
                                   0, 0, 0, 1);

SQStack *SQStack::instance()
{
    static QMutex mutex;
    if (!_instance)
    {
        mutex.lock();
        if (!_instance) _instance = new SQStack();
        mutex.unlock();
    }
    return _instance;
}

SQStack::SQStack() :
    _program(NULL),
    _perspectiveProvider(NULL),
    _stack()
{
}

void SQStack::init(QGLShaderProgram *program, IPerspectiveProvider *provider)
{
    Q_ASSERT(!_program);
    Q_ASSERT(!_perspectiveProvider);
    Q_ASSERT(_stack.isEmpty());
    _program = program;
    _perspectiveProvider = provider;
    _stack << IDENTITY;
}

SQStack::~SQStack()
{
}

SQStack *SQStack::apply()
{
    Q_ASSERT(_program);
    Q_ASSERT(_perspectiveProvider);
    Q_ASSERT(!_stack.isEmpty());
    _program->setUniformValue("mvp_matrix", mvpMatrix());
    return this;
}

SQStack *SQStack::push()
{
    _stack << QMatrix4x4(_stack.last());
    return this;
}

SQStack *SQStack::pop()
{
    Q_ASSERT(_stack.size() > 1);
    _stack.removeLast();
    return this;
}

SQStack *SQStack::loadIdentity()
{
    Q_ASSERT(!_stack.isEmpty());
    _stack.removeLast();
    _stack << IDENTITY;
    return this;
}

SQStack *SQStack::translate(qreal x, qreal y, qreal z)
{
    Q_ASSERT(!_stack.isEmpty());
    QMatrix4x4 m = _stack.takeLast();
    _stack << (m * QMatrix4x4(1, 0, 0, x,
                              0, 1, 0, y,
                              0, 0, 1, z,
                              0, 0, 0, 1));
    return this;
}

SQStack *SQStack::rotate(qreal angle, const QVector3D &vector)
{
    Q_ASSERT(!_stack.isEmpty());
    qreal u = vector.x();
    qreal v = vector.y();
    qreal w = vector.z();
    qreal u2 = u*u;
    qreal v2 = v*v;
    qreal w2 = w*w;
    qreal ct = cos(angle * PI / 180.0);
    qreal st = sin(angle * PI / 180.0);
    QMatrix4x4 m = _stack.takeLast();
    _stack << (m * QMatrix4x4(
                   u2 + (v2 + w2)*ct,
                   u*v*(1 - ct) - w*st,
                   u*w*(1 - ct) + v*st,
                   0,

                   u*v*(1 - ct) + w*st,
                   v2 + (u2 + w2)*ct,
                   v*w*(1 - ct) - u*st,
                   0,

                   u*w*(1 - ct) - v*st,
                   v*w*(1 - ct) + u*st,
                   w2 + (u2 + v2)*ct,
                   0,

                   0, 0, 0, 1
                   ));
    return this;
}
