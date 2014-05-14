/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQBlock.h"

SQBlock::Data SQBlock::create(const QDomDocument &doc)
{
    Data data;
    foreach (Type type, types())
    {
        QDomNodeList nodes = doc.elementsByTagName(typeToString(type));
        for (int i=0, n=nodes.count(); i<n; i++)
        {
            SP block = create(nodes.at(i).toElement(), type);
            Q_ASSERT_X(!data.blocks.contains(block->position()), "SQBlock::create",
                       QString("more than one block has position <%1,%2,%3>")
                       .arg(block->position().x())
                       .arg(block->position().y())
                       .arg(block->position().z())
                       .toStdString().c_str());
            data.blocks[block->position()] = block;
            if (block->type() == Source)
            {
                Q_ASSERT(block->id() != 0);
                Q_ASSERT_X(!data.sources.contains(block->id()), "SQBlock::create",
                           QString("more than one source has id %1")
                           .arg(block->id())
                           .toStdString().c_str());
                data.sources[block->id()] = block;
            }
            if (block->type() == Sink)
            {
                Q_ASSERT(block->id() != 0);
                Q_ASSERT_X(!data.sinks.contains(block->id()), "SQBlock::create",
                           QString("more than one sink has id %1")
                           .arg(block->id())
                           .toStdString().c_str());
                data.sinks[block->id()] = block;
            }
        }
    }

    QList<int> sourceKeys = data.sources.keys();
    QList<int> sinkKeys = data.sinks.keys();
    qSort(sourceKeys);
    qSort(sinkKeys);
    Q_ASSERT_X(sourceKeys == sinkKeys, "SQBlock::create",
               "there must be exactly one sink for every source");
    Q_ASSERT(!sourceKeys.isEmpty());
    Q_ASSERT(!sinkKeys.isEmpty());
    return data;
}

SQBlock::SQBlock(const QDomElement &elem, Type type) :
    QObject(0),
    _id(elem.attribute("id").toInt()),
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

int qHash(const QVector3D &v)
{
    static const int MAX_DIM = 100;
    return (int)v.x() * MAX_DIM * MAX_DIM +
            (int)v.y() * MAX_DIM +
            (int)v.z();
}
