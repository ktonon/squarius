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
#include <QGLShaderProgram>

class SQPuzzle : public QObject
{
    Q_OBJECT
public:
    typedef unsigned int World;
    typedef unsigned int Level;
    typedef QSharedPointer<SQPuzzle> SP;

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
    World world() const { return _world; }
    Level level() const { return _level; }

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

    World _world;
    Level _level;

    SQBlock::List _blocks;

    int _shape[3];
    QVector4D _i, _j, _k;
    QVector4D _origin;
    int _colIndex, _rowIndex;
};
