/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#pragma once
#include <SQOpenGL.h>
#include "IPerspectiveProvider.h"

class SQEngine;

/**
 * @brief OpenGL model/view matrix stack
 */
class SQStack
{
public:
    friend class SQEngine;

    /** @brief The identity matrix */
    static const QMatrix4x4 IDENTITY;

    static SQStack *instance();

    virtual ~SQStack();

    QMatrix4x4 modelViewMatrix() const { return _stack.last(); }
    QMatrix4x4 projectionMatrix() const { return _perspectiveProvider->perspective()->projectionMatrix(); }
    QMatrix4x4 mvpMatrix() const { return projectionMatrix() * modelViewMatrix(); }

    SQStack *apply();
    SQStack *push();
    SQStack *pop();
    SQStack *loadIdentity();
    SQStack *translate(qreal x, qreal y, qreal z);
    SQStack *rotate(qreal angle, const QVector3D &v);
    SQStack *replace(const QMatrix4x4 &m);

private:
    static SQStack *_instance;
    static qreal PI;

    SQStack();
    SQStack(const SQStack &); // hide copy constructor
    SQStack& operator=(const SQStack &); // hide assign op

    void init(QGLShaderProgram *program, IPerspectiveProvider *provider);

    QGLShaderProgram *_program; // weak
    IPerspectiveProvider *_perspectiveProvider; // weak
    QList<QMatrix4x4> _stack;
};
