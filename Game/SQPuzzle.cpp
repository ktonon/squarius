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

SQPuzzle::WorldMap SQPuzzle::worldMap()
{
    WorldMap map(new QHash<World,LevelList>);
    QDir puzzleDir(":/puzzles");
    foreach (const QFileInfo &info, puzzleDir.entryInfoList())
    {
        QStringList parts = info.baseName().split("-");
        World world = parts.at(0).toInt();
        Level level = parts.at(1).toInt();
        LevelList list = map->contains(world)
                ? map->value(world)
                : LevelList(new QList<Level>);
        list->append(level);
        map->insert(world, list);
    }
    foreach(const LevelList &list, map->values())
    {
        qSort(*list.data());
    }
    return map;
}

SQPuzzle::SQPuzzle(const Id &id) :
    QObject(0),
    _id(id),
    _shape(),
    _i(), _j(), _k(),
    _origin(),
    _colIndex(-1), _rowIndex(-1)
{
    QFile file(_id.path());
    if (file.exists())
    {
        QDomDocument doc;
        if (doc.setContent(&file))
        {
            _blockData = SQBlock::create(doc);
            _swarms = SQSwarm::create(doc);
            _waves = SQWave::create(doc);
            _towers = SQTower::create(doc);
        }
    }
    calcShapeOffset();
}

void SQPuzzle::calcShapeOffset()
{
    if (!blocks().isEmpty())
    {
        for (int dim=0; dim<3; dim++)
        {
            int minVal = blocks().first()->at(dim);
            int maxVal = minVal;
            foreach (const SQBlock::SP &block, blocks())
            {
                int val = block->at(dim);
                if (val < minVal) minVal = val;
                if (val > maxVal) maxVal = val;
            }
            _offset[dim] = minVal;
            _shape[dim] = maxVal - minVal + 1;
        }
    }
    Q_ASSERT(_shape[0] > 0 && _shape[1] > 0 && _shape[2] > 0);
}

SQPuzzle::~SQPuzzle()
{
}

void SQPuzzle::renderCells()
{
    foreach(SQBlock::SP block, blocks())
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
