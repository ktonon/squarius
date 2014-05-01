/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPuzzle.h"
#include "Utilities/SQPrimitives.h"
#include "Utilities/SQStack.h"
#include <QtXml>

SQPuzzle::SQPuzzle(SQPuzzle::World world, SQPuzzle::Level level) :
    QObject(0),
    _id(world, level),
    _blocks(),
    _swarms(),
    _waves(),
    _towers(),
    _shape(),
    _i(), _j(), _k(),
    _origin(),
    _colIndex(-1), _rowIndex(-1)
{
    QDomNodeList nodes;
    int i;
    int n;
    QFile file(_id.path());
    if (file.exists())
    {
        QDomDocument doc;
        if (doc.setContent(&file))
        {
            foreach (SQBlock::Type type, SQBlock::types())
            {
                nodes = doc.elementsByTagName(SQBlock::typeToString(type));
                for (i=0, n=nodes.count(); i<n; i++)
                {
                    QDomElement elem = nodes.at(i).toElement();
                    QStringList pos = elem.attribute("pos").split(' ');
                    _blocks << SQBlock::create(pos.at(0).toInt(),
                                               pos.at(1).toInt(),
                                               pos.at(2).toInt(),
                                               type);
                }
            }
            nodes = doc.elementsByTagName("swarm");
            for (i=0, n=nodes.count(); i<n; i++)
            {
                QDomElement elem = nodes.at(i).toElement();
                SQSwarm::SP swarm = SQSwarm::create(elem);
                _swarms[swarm->id()] = swarm;
                qDebug() << swarm->toString();
            }
            nodes = doc.elementsByTagName("wave");
            for (i=0, n=nodes.count(); i<n; i++)
            {
                QDomElement elem = nodes.at(i).toElement();
                _waves << SQWave::create(elem);
            }
            qSort(_waves);
            foreach (const SQWave::SP &wave, _waves)
                qDebug() << wave->toString();

            foreach (SQTower::Type type, SQTower::types())
            {
                nodes = doc.elementsByTagName(SQTower::typeToString(type));
                if (nodes.count() > 0)
                {
                    QDomElement elem = nodes.at(0).toElement();
                    SQTower::SP tower = SQTower::create(elem, type);
                    _towers[tower->type()] = tower;
                }
            }
            foreach (const SQTower::SP &tower, towers())
                qDebug() << tower->toString();
        }
    }
    calcShapeOffset();
}

void SQPuzzle::calcShapeOffset()
{
    if (!_blocks.isEmpty())
    {
        for (int dim=0; dim<3; dim++)
        {
            int minVal = _blocks.first()->at(dim);
            int maxVal = minVal;
            foreach (const SQBlock::SP &block, _blocks)
            {
                int val = block->at(dim);
                if (val < minVal) minVal = val;
                if (val > maxVal) maxVal = val;
            }
            _offset[dim] = minVal;
            _shape[dim] = maxVal - minVal + 1;
        }
    }
}

SQPuzzle::~SQPuzzle()
{
}

void SQPuzzle::renderCells()
{
    foreach(SQBlock::SP block, _blocks)
    {
        SQStack::instance()->push();
        SQStack::instance()->translate(
                    block->position().x() - _offset[0] - (float)_shape[0] / 2.0f + 0.5f,
                    block->position().y() - _offset[1] - (float)_shape[1] / 2.0f + 0.5f,
                    block->position().z() - _offset[2] - (float)_shape[2] / 2.0f + 0.5f, true)
                ->apply();
        SQPrimitives::instance()->drawCubeGeometry(block->color());
        SQStack::instance()->pop();
    }
}

void SQPuzzle::updateOrientation(const QMatrix4x4 &modelView)
{
    _i = modelView.column(0);
    _j = modelView.column(1);
    _k = modelView.column(2);
    QVector4D diagonal = _i + _j + _k;
    _origin = QVector4D(
            diagonal.x() > 0 ? 0 : (_shape[0] - 1),
            diagonal.y() > 0 ? 0 : (_shape[1] - 1),
            diagonal.z() > 0 ? 0 : (_shape[2] - 1),
            0);
    _colIndex = _i.x() ? 0 : (_i.y() ? 1 : 2);
    _rowIndex = _j.x() ? 0 : (_j.y() ? 1 : 2);
}
