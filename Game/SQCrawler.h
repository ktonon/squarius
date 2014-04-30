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

#ifndef SQCRAWLER_H
#define SQCRAWLER_H

#include <QtCore>

class SQCrawler : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        Crawler = 0,
        Limper,
        Walker,
        Jogger,
        Runner,
        Cycler,
        Glider,
        Undefined
    };

    static QList<Type> types()
    {
        QList<Type> types;
        for (int i=0, n=Undefined; i<n; i++)
            types << ((Type)i);
        return types;
    }

    typedef QSharedPointer<SQCrawler> SP;
    typedef QList<SP> List;

    static SP create(qint64 time, Type type) { return SP(new SQCrawler(time, type)); }
    virtual ~SQCrawler();

    /** @name Getters */
    /** @{ */
    qint64 time() const { return _time; }
    Type type() const { return _type; }
    /** @} */

    QString toString() const
    {
        return QString("%1 at %2")
                .arg(typeToString(_type))
                .arg(_time);
    }

    static QString typeToString(Type type)
    {
        switch(type)
        {
        case Crawler: return "crawler";
        case Limper: return "limper";
        case Walker: return "walker";
        case Jogger: return "jogger";
        case Runner: return "runner";
        case Cycler: return "cycler";
        case Glider: return "glider";
        default: return "undefined";
        }
    }

signals:

public slots:

private:
    explicit SQCrawler(qint64 time, Type type);

    Type _type;
    qint64 _time;
};

bool operator<(const SQCrawler::SP &a, const SQCrawler::SP &b);

#endif // SQCRAWLER_H
