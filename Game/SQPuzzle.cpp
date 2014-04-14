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

SQPuzzle::SQPuzzle(SQPuzzle::World world, SQPuzzle::Level level) :
    QObject(0),
    _world(world),
    _level(level),
    _blocks(),
    _shape(),
    _i(), _j(), _k(),
    _origin(),
    _colIndex(-1), _rowIndex(-1)
{
    // TODO: load from file
    _blocks
            << SQBlock::create(0, 0, 0)
            << SQBlock::create(0, 1, 0)
            << SQBlock::create(1, 0, 0)
            << SQBlock::create(1, 1, 0)
//            << SQBlock::create(0, 0, 1)
            << SQBlock::create(0, 1, 1)
            << SQBlock::create(1, 0, 1)
            << SQBlock::create(1, 1, 1)
            << SQBlock::create(0, 2, 0)
            << SQBlock::create(0, 3, 0)
            << SQBlock::create(0, 4, 0)
            << SQBlock::create(0, 4, 0)
            << SQBlock::create(1, 4, 0)
            << SQBlock::create(2, 4, 0)
            << SQBlock::create(3, 4, 0)
            << SQBlock::create(4, 4, 0)
            << SQBlock::create(4, 4, 1)
//            << SQBlock::create(4, 4, 2)
//            << SQBlock::create(4, 4, 3)
//            << SQBlock::create(4, 4, 4)
            << SQBlock::create(1, 0, 0)
            << SQBlock::create(2, 0, 0)
            << SQBlock::create(3, 0, 0)
            << SQBlock::create(4, 0, 0)
            << SQBlock::create(4, 0, 1)
//            << SQBlock::create(4, 0, 2)
//            << SQBlock::create(4, 0, 3)
//            << SQBlock::create(4, 0, 4)
//            << SQBlock::create(5, 5, 5)
//            << SQBlock::create(10, 10, 10)
//            << SQBlock::create(0, 10, 10)
//            << SQBlock::create(10, 0, 10)
//            << SQBlock::create(10, 10, 0)
            << SQBlock::create(10, 0, 0)
//            << SQBlock::create(0, 0, 10)
//            << SQBlock::create(0, 10, 0)
            ;
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
    qDebug() << "here";
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
                    block->position().z() - _offset[2] - (float)_shape[2] / 2.0f + 0.5f)
                ->apply();
        SQPrimitives::instance()->drawCubeGeometry();
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
