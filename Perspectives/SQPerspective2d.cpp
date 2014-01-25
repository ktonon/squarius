/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspective2d.h"

SQPerspective2d::SQPerspective2d(SQPuzzle::SP puzzle, QObject *parent) :
    SQPerspective(puzzle, parent)
{
}

SQPerspective2d::~SQPerspective2d()
{

}

void SQPerspective2d::setRatio(GLfloat ratio)
{
    // TODO: determine w and h from level shape.
    float h = (_puzzle->maxDimension() / 2.0f) * 1.1f;
    float w = h * ratio;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-w, w, -h, h, 1, 50);
    glGetFloatv(GL_PROJECTION_MATRIX, _projectionMatrix);
    glPopMatrix();
    // TODO: calculate 289.0f instead of hard coding it!
    _cellSize = 289.0f / _puzzle->maxDimension();
}

void SQPerspective2d::activate()
{

}

void SQPerspective2d::deactivate()
{

}

void SQPerspective2d::updateOrientation(const GLfloat* const modelView)
{

}
