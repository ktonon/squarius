/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include <QObject>

class SQPerspective : public QObject
{
    Q_OBJECT
public:
    explicit SQPerspective(QObject *parent = 0);
    virtual ~SQPerspective();

signals:

public slots:

};

#endif // PERSPECTIVE_H
