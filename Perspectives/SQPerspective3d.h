/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPERSPECTIVE3D_H
#define SQPERSPECTIVE3D_H

#include "SQPerspective.h"

class SQPerspective3d : public SQPerspective
{
    Q_OBJECT
public:
    explicit SQPerspective3d(QObject *parent = 0);
    virtual ~SQPerspective3d();

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

#endif // SQPERSPECTIVE3D_H
