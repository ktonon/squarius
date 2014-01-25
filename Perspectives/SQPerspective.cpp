/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspective.h"

SQPerspective::SQPerspective(SQPuzzle::SP puzzle, QObject *parent) :
    QObject(parent),
    _puzzle(puzzle),
    _projectionMatrix()
{
}

SQPerspective::~SQPerspective()
{
}
