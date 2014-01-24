/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPERSPECTIVESWITCHER_H
#define SQPERSPECTIVESWITCHER_H

#include "SQPerspective.h"

class SQPerspectiveSwitcher : public SQPerspective
{
    Q_OBJECT
public:
    explicit SQPerspectiveSwitcher(SQPerspective* start, SQPerspective* end, QObject *parent = 0);
    virtual ~SQPerspectiveSwitcher();

    /** @name Getters */
    /** @{ */
    SQPerspective* startPerspective() const { return _startPerspective; }
    SQPerspective* endPerspective() const { return _endPerspective; }
    /** @} */

    /** @name SQPerspective interface */
    /** @{ */
    virtual void setRatio(GLfloat ratio);
    virtual void renderModel();
    virtual void activate();
    virtual void deactivate();
    virtual void updateOrientation(GLfloat const* modelView);
    /** @} */

signals:

public slots:

private:
    SQPerspective* _startPerspective;
    SQPerspective* _endPerspective;
};

#endif // SQPERSPECTIVESWITCHER_H
