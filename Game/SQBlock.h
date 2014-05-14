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
#include <QtXml>
#include <QVector3D>
#include <QVector4D>
#include <math.h>

class SQBlock : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        Cell = 0,
        Speed,
        Health,
        Solid,
        Source,
        Sink,
        Undefined
    };

    static QList<Type> types()
    {
        QList<Type> types;
        for (int i=0, n=Undefined; i<n; i++)
            types << ((Type)i);
        return types;
    }

    typedef QSharedPointer<SQBlock> SP;
    typedef QList<SP> List;
    typedef QHash<int,SP> HashById;
    typedef QHash<QVector3D,SP> HashByPos;

    struct Data
    {
        HashById sources;
        HashById sinks;
        HashByPos blocks;
    };

    static Data create(const QDomDocument &doc);
    static SP create(const QDomElement &elem, Type type) { return SP(new SQBlock(elem, type)); }
    virtual ~SQBlock();

    /** @name Getters */
    /** @{ */
    int id() const { return _id; }
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
        return QString("Block with type %1")
                .arg(typeToString(_type));
    }

    QVector4D color() const;

    static QString typeToString(Type type)
    {
        switch(type)
        {
        case Cell: return "cell";
        case Speed: return "speed";
        case Health: return "health";
        case Solid: return "solid";
        case Source: return "source";
        case Sink: return "sink";
        default: return "undefined";
        }
    }

private:
    explicit SQBlock(const QDomElement &elem, Type type);

    int _id;
    QVector3D _position;
    Type _type;
};

int qHash(const QVector3D &v);

#endif // SQBLOCK_H
