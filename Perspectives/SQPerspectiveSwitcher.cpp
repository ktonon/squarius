/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspectiveSwitcher.h"
#include "Utilities/Matrix.h"

SQPerspectiveSwitcher::SQPerspectiveSwitcher(SQPerspective *start, SQPerspective *end, int duration, QObject *parent) :
    SQPerspective(start->maxDimension(), parent),
    _startPerspective(start),
    _endPerspective(end),
    _timer(),
    _startedAt()
{
    _timer.setSingleShot(true);
    _timer.setInterval(duration);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(deactivate()));
    connect(this, SIGNAL(activated()), start, SLOT(deactivate()));
    connect(this, SIGNAL(deactivated()), end, SLOT(activate()));
}

SQPerspectiveSwitcher::~SQPerspectiveSwitcher()
{

}

void SQPerspectiveSwitcher::setRatio(GLfloat ratio)
{

}

void SQPerspectiveSwitcher::activate()
{
    Q_ASSERT(_startedAt.isNull());
    sqMatrixCopy(_projectionMatrix, _startPerspective->projectionMatrix());
    _startedAt = QDateTime::currentDateTime();
    _timer.start();
    SQPerspective::activate();
}
