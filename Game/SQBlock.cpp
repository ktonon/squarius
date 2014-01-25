/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQBlock.h"

SQBlock::SQBlock(const SQPointI &position, Type type) :
    QObject(0),
    _position(position),
    _type(type)
{
}

SQBlock::~SQBlock()
{
}
