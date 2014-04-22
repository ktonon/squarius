/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspective3d.h"
#include "Utilities/Matrix.h"

SQPerspective3d::SQPerspective3d(int maxDimension, QObject *parent) :
    SQPerspective(maxDimension, parent)
{
}

SQPerspective3d::~SQPerspective3d()
{

}

void SQPerspective3d::setShape(int w, int h)
{
    float x = _maxDimension * 0.4f;
    float y = x;
    float ratio = (float)w / h;
    if (ratio > 1)
        x = y * ratio;
    else
        y = x / ratio;

    _projectionMatrix.setToIdentity();
    _projectionMatrix.frustum(-x, x,
                              -y, y,
                              SQ_NEAR, SQ_FAR);
//    _projectionMatrix.frustum(-w, w, -h, h, SQ_NEAR, SQ_FAR);
}

void SQPerspective3d::activate()
{
    qDebug() << QString("3d activated\n%1").arg(sqMatrixToString(_projectionMatrix));
    SQPerspective::activate();
}

void SQPerspective3d::deactivate()
{
    qDebug() << "3d deactivated";
    SQPerspective::deactivate();
}
