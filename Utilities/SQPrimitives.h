/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#pragma once
#include <QtOpenGL>
#include <QGLShaderProgram>

class SQEngine;

class SQPrimitives : protected QGLFunctions
{
public:
    friend class SQEngine;

    static SQPrimitives *instance();

    virtual ~SQPrimitives();

    void drawCubeGeometry();

private:
    static SQPrimitives *_instance;

    SQPrimitives();
    SQPrimitives(const SQPrimitives &); // hide copy constructor
    SQPrimitives& operator=(const SQPrimitives &); // hide assign op

    void init(QGLShaderProgram *program);
    void initCubeGeometry();

    QGLShaderProgram *_program; // weak
    GLuint _vboIds[2];
};
