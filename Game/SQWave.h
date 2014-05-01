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

#ifndef SQWAVE_H
#define SQWAVE_H

#include <QtCore>
#include <QtXml>

class SQWave : public QObject
{
    Q_OBJECT
public:

    typedef QSharedPointer<SQWave> SP;
    typedef QList<SP> List;

    static SP create(const QDomElement &elem) { return SP(new SQWave(elem)); }
    virtual ~SQWave();

    /** @name Getters */
    /** @{ */
    int swarmId() const { return _swarmId; }
    float strength() const { return _strength; }
    qint64 time() const { return _time; }
    /** @} */

    QString toString() const
    {
        return QString("wave(swarmId=%1, sourceId=%2) x %3 at %4")
                .arg(_swarmId)
                .arg(_sourceId)
                .arg(_strength)
                .arg(_time);
    }

signals:

public slots:

private:
    explicit SQWave(const QDomElement &elem);

    int _swarmId;
    int _sourceId;
    float _strength;
    qint64 _time;
};

bool operator<(const SQWave::SP &a, const SQWave::SP &b);

#endif // SQWAVE_H
