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

void SQPerspective2d::setRatio(GLfloat ratio)
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
    _projectionMatrix.ortho(w, w, h, h, n, f);

    // TODO: calculate 289.0f instead of hard coding it!
    _cellSize = 289.0f / _maxDimension;
}

void SQPerspective2d::activate()
{
    qDebug() << QString("2d activated\n%1").arg(sqMatrixToString(_projectionMatrix));
    SQPerspective::activate();
}

void SQPerspective2d::deactivate()
{
    qDebug() << "2d deactivated";
    SQPerspective::deactivate();
}
