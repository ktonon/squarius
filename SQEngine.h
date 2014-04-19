/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#pragma once
#include "SQOpenGL.h"
#include "Gestures/SQPanGestureRecognizer.h"
#include <QtCore>
#include <QtGui>
#include <QPanGesture>
#include <QPinchGesture>
#include <QTapGesture>
class SQPuzzleEngine;


class SQEngine : public QGLWidget, public QGLFunctions
{
    Q_OBJECT
public:
    static const int FRAMES_PER_SECOND;

    explicit SQEngine(QWidget *parent = 0);
    virtual ~SQEngine();

    virtual bool event(QEvent *event);
    bool gestureEvent(QGestureEvent *event);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    void initShaders();
    void initTextures();

    virtual void timerEvent(QTimerEvent *);

    QString toString() const;

signals:
    void perspectiveChanged();

public slots:
    void togglePerspective();

private:
    QGLShaderProgram _shaderProgram;
    QBasicTimer _renderTimer;

    SQPuzzleEngine* _puzzleEngine;
    GLuint _texture;
    GLint _height;
    GLint _width;
};
