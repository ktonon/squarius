/**
 @file
 @author D2L Capture Team <dev@captual.com>
 @section LICENSE

 2008 - 2013 Desire2Learn Inc.
 All Rights Reserved.

 NOTICE:  All information contained herein is, and remains the property of
 Desire2Learn Incorporated and its suppliers, if any.  Dissemination of this
 information or reproduction of this material is strictly forbidden unless
 prior written permission is obtained from Desire2Learn Incorporated.
 */

#ifndef SQTOWER_H
#define SQTOWER_H

#include <QtCore>
#include <QtXml>

class SQTower : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        Blaster = 0,
        Thumper,
        Laser,
        Missile,
        Shock,
        Portal,
        Undefined
    };

    static QList<Type> types()
    {
        QList<Type> types;
        for (int i=0, n=Undefined; i<n; i++)
            types << ((Type)i);
        return types;
    }

    typedef QSharedPointer<SQTower> SP;
    typedef QList<SP> List;
    typedef QHash<Type,SP> Hash;

    static SP create(const QDomElement &elem, Type type) { return SP(new SQTower(elem, type)); }
    virtual ~SQTower();

    /** @name Getters */
    /** @{ */
    float cost() const { return _cost; }
    Type type() const { return _type; }
    /** @} */

    QString toString() const
    {
        return QString("%1 costing %2")
                .arg(typeToString(_type))
                .arg(_cost);
    }

    static QString typeToString(Type type)
    {
        switch(type)
        {
        case Blaster: return "blaster";
        case Thumper: return "thumper";
        case Laser: return "laser";
        case Missile: return "missile";
        case Shock: return "shock";
        case Portal: return "portal";
        default: return "undefined";
        }
    }

signals:

public slots:

private:
    explicit SQTower(const QDomElement &elem, Type type);

    Type _type;
    float _cost;
};

bool operator<(const SQTower::SP &a, const SQTower::SP &b);

#endif // SQTOWER_H
