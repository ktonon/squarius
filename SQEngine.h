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

    /** @name Predicates */
    /** @{ */
    bool isPerspectiveSwitching() const { return _perspective != NULL && _perspective == _perspectiveSwitcher; }
    bool isPerspective2d() const { return _perspective == _perspective2d; }
    bool isPerspective3d() const { return _perspective == _perspective3d; }
    bool shouldPullViewToAxis() const
    {
        return (_isCubeLocked || isPerspectiveSwitching() || isPerspective2d())
                && !_isGesturing;
    }
    /** @} */

    /** @name Getters */
    /** @{ */
    SQPerspective* otherPerspective() const
    {
        Q_ASSERT(_perspective != NULL);
        return isPerspectiveSwitching()
                ? _perspectiveSwitcher->startPerspective()
                : (isPerspective2d()
                   ? dynamic_cast<SQPerspective*>(_perspective3d)
                   : dynamic_cast<SQPerspective*>(_perspective2d) );
    }
    /** @} */

    /** @name ModelView modifiers */
    /** @{ */
    void applyGesturesToModelView();
    void pullViewToAxis();
    /** @} */

signals:

public slots:

private:

    static const GLfloat NEAR;

    SQPerspective* _perspective;
    SQPerspective2d* _perspective2d;
    SQPerspective3d* _perspective3d;
    SQPerspectiveSwitcher* _perspectiveSwitcher;

    bool _isCubeLocked;
    bool _isGesturing;

    GLfloat _lastModelView[16];
    GLfloat _rotI;
    GLfloat _rotJ;
    GLfloat _rotK;
    bool _isFirstRender;

    GLfloat _offset;

};

#endif // GLWIDGET_H
