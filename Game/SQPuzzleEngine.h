/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPUZZLEENGINE_H
#define SQPUZZLEENGINE_H

#include "SQPerspectives.h"
#include "SQPuzzle.h"
#include "SQTypes.h"
#include <QObject>


class SQPuzzleEngine : public QObject
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

    /** @name Getters */
    /** @{ */
    SQPuzzle::SP puzzle() const { return _puzzle; }

    const GLfloat* modelViewMatrix() { return _modelViewMatrix; }

    const GLfloat* projectionMatrix() { return _perspective->projectionMatrix(); }

    GLfloat distanceToModelView() const { return SQ_NEAR * 1.5f + _offset; }

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

    void updateModelView()
    {
        applyGesturesToModelView();
        if (shouldPullViewToAxis()) pullViewToAxis();
    }

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

    GLfloat _modelViewMatrix[SQ_MATRIX_SIZE];
    GLfloat _rotI;
    GLfloat _rotJ;
    GLfloat _rotK;
    bool _isFirstRender;

    GLfloat _offset;
};

#endif // SQPUZZLEENGINE_H
