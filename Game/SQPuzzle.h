/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#pragma once
#include <QtCore>
#include "SQOpenGL.h"
#include "SQBlock.h"
#include "SQSwarm.h"
#include "SQTower.h"
#include "SQWave.h"
#include <QGLShaderProgram>

class SQPuzzle : public QObject
{
    Q_OBJECT
public:
    typedef quint64 World;
    typedef quint8 Level;
    typedef QSharedPointer<SQPuzzle> SP;

    class Id
    {
    public:
        Id(World world, Level level) : _world(world), _level(level) {}

        World world() const { return _world; }
        Level level() const { return _level; }
        QString filename() const
        {
            return QString("%1-%2.xml")
                    .arg(_world, 16, 16, QChar('0'))
                    .arg(_level, 2, 16, QChar('0'));
        }
        QString path() const
        {
            return QString(":/puzzles/%1").arg(filename());
        }

    private:
        World _world;
        Level _level;
    };

    typedef QSharedPointer<QList<Level> > LevelList;
    typedef QSharedPointer<QHash<World,LevelList> > WorldMap;

    static WorldMap worldMap();

    /**
     * @brief Load a puzzle for the given world and level
     * @param world The package of puzzle levels in which to look for the level
     * @param level The level number, relative to the world
     * @return A shared pointer to the loaded puzzle
     */
    static SP load(const Id &id) { return SP(new SQPuzzle(id)); }
    virtual ~SQPuzzle();

    /** @name Getters */
    /** @{ */
    Level level() const { return _id.level(); }
    World world() const { return _id.world(); }
    int maxDimension() const { return fmaxf(fmaxf(_shape[0], _shape[1]), _shape[2]); }

    SQBlock::SP block(int x, int y, int z) const { return block(QVector3D(x, y, z)); }
    SQBlock::SP block(const QVector3D &pos) const { return _blockData.blocks[pos]; }
    SQBlock::List blocks() const { return _blockData.blocks.values(); }
    SQBlock::SP sink(int id) const { return _blockData.sinks[id]; }
    SQBlock::SP source(int id) const { return _blockData.sources[id]; }
    /** @} */

    /** @name Commands */
    /** @{ */
    void renderCells();

    /**
     * @brief Update orientation
     * @param modelView The model view matrix
     */
    void updateOrientation(const QMatrix4x4& modelView);
    /** @} */

signals:

public slots:

private:
    explicit SQPuzzle(const Id &id);
    void calcShapeOffset();

    Id _id;
    SQBlock::Data _blockData;
    SQSwarm::Hash _swarms;
    SQWave::List _waves;
    SQTower::Hash _towers;

    int _shape[3];
    int _offset[3];

    QVector4D _i, _j, _k;
    QVector4D _origin;
    int _colIndex, _rowIndex;
};
