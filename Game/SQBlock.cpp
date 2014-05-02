/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQBlock.h"

SQBlock::List SQBlock::create(const QDomDocument &doc)
{
    List blocks;
    foreach (Type type, types())
    {
        QDomNodeList nodes = doc.elementsByTagName(typeToString(type));
        for (int i=0, n=nodes.count(); i<n; i++)
            blocks << create(nodes.at(i).toElement(), type);
    }
    return blocks;
}

SQBlock::SQBlock(const QDomElement &elem, Type type) :
    QObject(0),
    _type(type)
{
    QStringList pos = elem.attribute("pos").split(' ');
    _position = QVector3D(pos.at(0).toInt(),
                          pos.at(1).toInt(),
                          pos.at(2).toInt());
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

