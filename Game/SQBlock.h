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
#include <QVector3D>
#include <math.h>

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

    static SP create(Type type = Concrete) { return SP(new SQBlock(QVector3D(), type)); }
    static SP create(int x, int y, int z, Type type = Concrete) { return SP(new SQBlock(QVector3D(x, y, z), type)); }
    static SP create(const QVector3D &position, Type type = Concrete) { return SP(new SQBlock(position, type)); }
    virtual ~SQBlock();

    /** @name Getters */
    /** @{ */
    QVector3D position() const { return _position; }
    float at(int dim) const
    {
        switch(dim)
        {
        case 0: return _position.x();
        case 1: return _position.y();
        case 2: return _position.z();
        default: return 0;
        }
    }
    Type type() const { return _type; }
    /** @} */

    QString toString() const
    {
        return QString("Block with type %2")
//                .arg(_position.toString())
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
    explicit SQBlock(const QVector3D &position, Type type = Concrete);

    QVector3D _position;
    Type _type;
};

#endif // SQBLOCK_H
