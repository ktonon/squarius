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

    /**
     * @brief Load a puzzle for the given world and level
     * @param world The package of puzzle levels in which to look for the level
     * @param level The level number, relative to the world
     * @return A shared pointer to the loaded puzzle
     */
    static SP load(World world, Level level) { return SP(new SQPuzzle(world, level)); }
    virtual ~SQPuzzle();

    /** @name Getters */
    /** @{ */
    World world() const { return _id.world(); }
    Level level() const { return _id.level(); }

    int maxDimension() const { return fmaxf(fmaxf(_shape[0], _shape[1]), _shape[2]); }
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
    explicit SQPuzzle(World world, Level level);
    void calcShapeOffset();

    Id _id;
    SQBlock::List _blocks;
    SQSwarm::Hash _swarms;
    SQWave::List _waves;

    int _shape[3];
    int _offset[3];

    QVector4D _i, _j, _k;
    QVector4D _origin;
    int _colIndex, _rowIndex;
};
