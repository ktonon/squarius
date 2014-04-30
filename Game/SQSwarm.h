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

#ifndef SQSWARM_H
#define SQSWARM_H

#include <QtCore>
#include <QtXml>
#include "SQCrawler.h"

class SQSwarm : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<SQSwarm> SP;
    typedef QHash<int,SP> Hash;

    static SP create(const QDomElement &elem) { return SP(new SQSwarm(elem)); }
    virtual ~SQSwarm();

    /** @name Getters */
    /** @{ */
    int id() const { return _id; }
    SQCrawler::List crawlers() const { return _crawlers; }
    /** @} */

    QString toString() const
    {
        QStringList l;
        foreach (const SQCrawler::SP &c, _crawlers)
            l << c->toString();
        return QString("swarm(%1)\n{\n  %2\n}")
                .arg(_id)
                .arg(l.join("\n  "));
    }
signals:

public slots:

private:
    explicit SQSwarm(const QDomElement &elem);

    int _id;
    SQCrawler::List _crawlers;
};

#endif // SQSWARM_H
