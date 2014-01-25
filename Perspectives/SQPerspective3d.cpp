/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspective3d.h"

SQPerspective3d::SQPerspective3d(SQPuzzle::SP puzzle, QObject *parent) :
    SQPerspective(puzzle, parent)
{
}

SQPerspective3d::~SQPerspective3d()
{

}

void SQPerspective3d::setRatio(GLfloat ratio)
{
    float h = _puzzle->maxDimension() / 2.0f;
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

}

void SQPerspective3d::deactivate()
{

}

void SQPerspective3d::updateOrientation(const GLfloat* const modelView)
{

}
