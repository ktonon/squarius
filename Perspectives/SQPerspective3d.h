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
    explicit SQPerspective3d(int maxDimension, QObject *parent = 0);
    virtual ~SQPerspective3d();

    /** @name SQPerspective interface */
    /** @{ */
    virtual void setShape(int w, int h);
public slots:
    virtual void activate();
    virtual void deactivate();
    /** @} */

};

#endif // SQPERSPECTIVE3D_H
