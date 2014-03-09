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
    explicit SQPerspective2d(int maxDimension, QObject *parent = 0);
    virtual ~SQPerspective2d();

    /** @name SQPerspective interface */
    /** @{ */
    virtual void setRatio(GLfloat ratio);

    virtual void setShape(int w, int h);

public slots:
    virtual void activate();
    virtual void deactivate();
    /** @} */

private:
    GLfloat _cellSize;

};

#endif // SQPERSPECTIVE2D_H
