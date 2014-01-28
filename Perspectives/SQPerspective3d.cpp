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
    _projectionMatrix[0] = n / w;
    _projectionMatrix[5] = n / h;
    _projectionMatrix[10] = - (f + n) / (f - n);
    _projectionMatrix[11] = -1.0f;
    _projectionMatrix[14] = -2.0f * f * n / (f - n);
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
