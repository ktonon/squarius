/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtCore>
#include "SQOpenGL.h"
class SQPuzzleEngine;


class SQEngine : public QGLWidget, public QGLFunctions
{
    Q_OBJECT
public:
    static const int FRAMES_PER_SECOND;

    explicit SQEngine(QWidget *parent = 0);
    virtual ~SQEngine();

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    void initShaders();

    virtual void timerEvent(QTimerEvent *);

public slots:
    void togglePerspective();

private:
    QGLShaderProgram _shaderProgram;
    QBasicTimer _renderTimer;
    SQPuzzleEngine* _puzzleEngine;
    GLint _height;
    GLint _width;
};

#endif // GLWIDGET_H
