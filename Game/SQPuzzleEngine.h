/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPUZZLEENGINE_H
#define SQPUZZLEENGINE_H

#include "IPerspectiveProvider.h"
#include "SQPerspectives.h"
#include "SQPuzzle.h"
#include "SQTypes.h"
#include "SQOpenGL.h"


class SQPuzzleEngine : public QObject, public QGLFunctions, public IPerspectiveProvider
{
    Q_OBJECT
public:
    explicit SQPuzzleEngine(SQPuzzle::SP puzzle, QObject *parent = 0);
    virtual ~SQPuzzleEngine();

    /** @name Predicates */
    /** @{ */
    bool isActive() const { return _isActive; }
    bool isPerspectiveSwitching() const { return _perspective != NULL && _perspective == _perspectiveSwitcher; }
    bool isPerspective2d() const { return _perspective == _perspective2d; }
    bool isPerspective3d() const { return _perspective == _perspective3d; }
    /** @} */

    /** @name IPerspectiveProvider methods */
    /** @{ */

    virtual SQPerspective *perspective() const { return _perspective; }

    /** @} */

    /** @name Getters */
    /** @{ */

    SQPuzzle::SP puzzle() const { return _puzzle; }

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

signals:
    void perspectedSwitchEnded();

public slots:

    /** @name Commands */
    /** @{ */
    void activate()
    {
        if (!_isActive)
        {
            _isActive = true;
            _perspective->activate();
        }
    }

    void setRatio(GLfloat ratio)
    {
        _perspective2d->setRatio(ratio);
        _perspective3d->setRatio(ratio);
        if (_perspectiveSwitcher != NULL)
            _perspectiveSwitcher->setRatio(ratio);
    }

    void setShape(int w, int h)
    {
        _perspective2d->setShape(w, h);
        _perspective3d->setShape(w, h);
        if (_perspectiveSwitcher != NULL)
            _perspectiveSwitcher->setShape(w, h);
    }

    void updateModelView();

    void perspectiveSwitchBegin();

    void perspectiveSwitchEnd();

    void renderModel();
    /** @} */

private:
    void applyGesturesToModelView();
    void pullViewToAxis();
    bool shouldPullViewToAxis() const
    {
        return (_isCubeLocked || isPerspectiveSwitching() || isPerspective2d())
                && !_isGesturing;
    }

    SQPuzzle::SP _puzzle;

    SQPerspective* _perspective;
    SQPerspective2d* _perspective2d;
    SQPerspective3d* _perspective3d;
    SQPerspectiveSwitcher* _perspectiveSwitcher;

    bool _isActive;
    bool _isCubeLocked;
    bool _isGesturing;

    GLfloat _rotI;
    GLfloat _rotJ;
    GLfloat _rotK;
    bool _isFirstRender;

    GLfloat _offset;
};

#endif // SQPUZZLEENGINE_H
