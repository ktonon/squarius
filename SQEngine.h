/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "SQPerspectives.h"

class SQEngine : public QGLWidget
{
    Q_OBJECT
public:
    explicit SQEngine(QWidget *parent = 0);
    virtual ~SQEngine();

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

signals:

public slots:

private:
    SQPerspective* _perspective;
    SQPerspective2d* _perspective2d;
    SQPerspective3d* _perspective3d;
    SQPerspectiveSwitcher* _perspectiveSwitcher;

};

#endif // GLWIDGET_H
