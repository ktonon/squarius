/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPuzzle.h"

SQPuzzle::SQPuzzle(SQPuzzle::World world, SQPuzzle::Level level) :
    QObject(0),
    _world(world),
    _level(level)
{

}

SQPuzzle::~SQPuzzle()
{
}

void SQPuzzle::renderCells()
{

}
