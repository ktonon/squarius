/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPERSPECTIVE2D_H
#define SQPERSPECTIVE2D_H

#include "SQPerspective.h"

class SQPerspective2d : public SQPerspective
{
    Q_OBJECT
public:
    explicit SQPerspective2d(QObject *parent = 0);
    virtual ~SQPerspective2d();

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

};

#endif // SQPERSPECTIVE2D_H
