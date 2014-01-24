/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspective.h"

SQPerspective::SQPerspective(QObject *parent) :
    QObject(parent),
    _projectionMatrix()
{
}

SQPerspective::~SQPerspective()
{
}
