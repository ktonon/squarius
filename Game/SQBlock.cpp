/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQBlock.h"

SQBlock::SQBlock(const QVector3D &position, Type type) :
    QObject(0),
    _position(position),
    _type(type)
{
}

SQBlock::~SQBlock()
{
}

QVector4D SQBlock::color() const
{
    switch(_type)
    {
    case Cell: return QVector4D(0.5, 0.5, 0.5, 0.5);
    case Speed: return QVector4D(0, 1, 1, 1);
    case Health: return QVector4D(1, 1, 0, 1);
    case Solid: return QVector4D(1, 0, 1, 1);
    case Source: return QVector4D(0, 1, 0, 1);
    case Sink: return QVector4D(1, 0, 0, 1);
    default: return QVector4D(0, 0, 0, 0);
    }
}

