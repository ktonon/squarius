/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQBLOCK_H
#define SQBLOCK_H

#include <QtCore>
#include "SQMath.h"

class SQBlock : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        Undefined,
        Concrete,
        Box
    };

    typedef QSharedPointer<SQBlock> SP;
    typedef QList<SP> List;

    static SP create(Type type = Concrete) { return SP(new SQBlock(SQPointI(), type)); }
    static SP create(int x, int y, int z, Type type = Concrete) { return SP(new SQBlock(SQPointI(x, y, z), type)); }
    static SP create(const SQPointI& position, Type type = Concrete) { return SP(new SQBlock(position, type)); }
    virtual ~SQBlock();

    /** @name Getters */
    /** @{ */
    SQPointI position() const { return _position; }
    Type type() const { return _type; }
    /** @} */

    QString toString() const
    {
        return QString("Block at %1 with type %2")
                .arg(_position.toString())
                .arg(typeToString(_type));
    }

    static QString typeToString(Type type)
    {
        switch(type)
        {
        case Concrete: return "Concrete";
        case Box: return "Box";
        default: return "Undefined";
        }
    }

private:
    explicit SQBlock(const SQPointI& position, Type type = Concrete);

    SQPointI _position;
    Type _type;
};

#endif // SQBLOCK_H
