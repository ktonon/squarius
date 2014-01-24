/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPERSPECTIVESWITCHER_H
#define SQPERSPECTIVESWITCHER_H

#include "SQPerspective.h"

class SQPerspectiveSwitcher : public SQPerspective
{
    Q_OBJECT
public:
    explicit SQPerspectiveSwitcher(QObject *parent = 0);
    virtual ~SQPerspectiveSwitcher();

signals:

public slots:

};

#endif // SQPERSPECTIVESWITCHER_H
