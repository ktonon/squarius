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
    float h = (_maxDimension / 2.0f) * 1.1f;
    float w = h * ratio;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-w, w, -h, h, 1, 50);
    glGetFloatv(GL_PROJECTION_MATRIX, _projectionMatrix);
    glPopMatrix();
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
