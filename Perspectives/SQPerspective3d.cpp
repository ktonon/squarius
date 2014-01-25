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
    float h = _maxDimension / 2.0f;
    float w = h * ratio;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glFrustum(-w, w, -h, h, SQ_NEAR, SQ_NEAR * 2.0f + h * 2.0f);
    glGetFloatv(GL_PROJECTION_MATRIX, _projectionMatrix);
    glPopMatrix();
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
