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

#include <QObject>

class SQTower : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        Blaster,
        Thumper,
        Laser,
        Missile,
        Shock,
        Portal
    };

    explicit SQTower(QObject *parent = 0);

signals:

public slots:

};

#endif // SQTOWER_H
