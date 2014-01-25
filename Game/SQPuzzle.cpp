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
    _level(level),
    _blocks(),
    _shape(),
    _i(), _j(), _k(),
    _origin(),
    _colIndex(-1), _rowIndex(-1)
{
    // TODO: load from file
    _shape[0] = 5;
    _shape[1] = 5;
    _shape[2] = 5;

    _blocks << SQBlock::create(0,1,0);
}

SQPuzzle::~SQPuzzle()
{
}

void SQPuzzle::renderCells()
{

}

void SQPuzzle::updateOrientation(const GLfloat * const modelView)
{
    _i = SQVectorI(modelView[0], modelView[4], modelView[8]);
    _j = SQVectorI(modelView[1], modelView[5], modelView[9]);
    _k = SQVectorI(modelView[2], modelView[6], modelView[10]);
    SQVectorI diagonal = _i + _j + _k;
    _origin = SQPointI(diagonal.u > 0 ? 0 : (_shape[0] - 1),
                       diagonal.v > 0 ? 0 : (_shape[1] - 1),
                       diagonal.w > 0 ? 0 : (_shape[2] - 1));
    _colIndex = _i.u ? 0 : (_i.v ? 1 : 2);
    _rowIndex = _j.u ? 0 : (_j.v ? 1 : 2);

    qDebug() << QString("\nOrientation\n%1\n%2\n%3").arg(_i.toString()).arg(_j.toString()).arg(_k.toString())
             << "\nOrigin\n" << _origin.toString()
             << QString("\nCol and row indices: %1, %2").arg(_colIndex).arg(_rowIndex);
}
