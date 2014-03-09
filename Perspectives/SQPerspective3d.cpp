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

void SQPerspective3d::setRatio(GLfloat ratio)
{
    float w, h, n, f;
    if (ratio > 1)
    {
        h = (_maxDimension / 2.0f) * 1.1f;
        w = h * ratio;
    }
    else
    {
        w = (_maxDimension / 2.0f) * 1.1f;
        h = w / ratio;
    }
    n = SQ_NEAR;
    f = SQ_NEAR * _maxDimension;
    _projectionMatrix.setToIdentity();
    _projectionMatrix.frustum(-w, w, -h, h, n, f);
    //    _projectionMatrix.perspective(60, ratio, 1.0, 100.0);
}

void SQPerspective3d::setShape(int w, int h)
{
    float k = _maxDimension;
    _projectionMatrix.setToIdentity();
    _projectionMatrix.frustum(-k, k,
                              -k, k,
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
