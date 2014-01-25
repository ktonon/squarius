/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspective.h"

SQPerspective::SQPerspective(int maxDimension, QObject *parent) :
    QObject(parent),
    _projectionMatrix(),
    _maxDimension(maxDimension)
{
}

SQPerspective::~SQPerspective()
{
}

void SQPerspective::activate()
{
    emit activated();
}

void SQPerspective::deactivate()
{
    emit deactivated();
}
