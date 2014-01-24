/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPUZZLE_H
#define SQPUZZLE_H

#include <QtCore>

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
    /** @} */

signals:

public slots:

private:
    explicit SQPuzzle(World world, Level level);

    World _world;
    Level _level;
};

#endif // SQPUZZLE_H
