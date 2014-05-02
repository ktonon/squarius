/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspective2d.h"
#include "Utilities/Matrix.h"

SQPerspective2d::SQPerspective2d(int maxDimension, QObject *parent) :
    SQPerspective(maxDimension, parent)
{
}

SQPerspective2d::~SQPerspective2d()
{
}

void SQPerspective2d::setShape(int w, int h)
{
    float x = _maxDimension * 0.55f;
    float y = x;
    float ratio = (float)w / h;
    if (ratio > 1)
        x = y * ratio;
    else
        y = x / ratio;

    _cellSize = w > h
            ? h / _maxDimension
            : w / _maxDimension;
    _projectionMatrix.setToIdentity();
    _projectionMatrix.ortho(-x, x,
                            -y, y,
                            SQ_NEAR, SQ_FAR);
}

void SQPerspective2d::activate()
{
    SQPerspective::activate();
}

void SQPerspective2d::deactivate()
{
    SQPerspective::deactivate();
}
