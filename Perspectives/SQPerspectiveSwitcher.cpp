/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspectiveSwitcher.h"

SQPerspectiveSwitcher::SQPerspectiveSwitcher(SQPerspective *start, SQPerspective *end, QObject *parent) :
    SQPerspective(parent),
    _startPerspective(start),
    _endPerspective(end)
{
}

SQPerspectiveSwitcher::~SQPerspectiveSwitcher()
{

}

void SQPerspectiveSwitcher::setRatio(GLfloat ratio)
{

}

void SQPerspectiveSwitcher::renderModel()
{

}

void SQPerspectiveSwitcher::activate()
{

}

void SQPerspectiveSwitcher::deactivate()
{

}

void SQPerspectiveSwitcher::updateOrientation(GLfloat const* modelView)
{

}
