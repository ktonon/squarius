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
class SQPuzzleEngine;


class SQEngine : public QGLWidget
{
    Q_OBJECT
public:
    explicit SQEngine(QWidget *parent = 0);
    virtual ~SQEngine();

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

public slots:
    void togglePerspective();

private:
    SQPuzzleEngine* _puzzleEngine;
};

#endif // GLWIDGET_H
