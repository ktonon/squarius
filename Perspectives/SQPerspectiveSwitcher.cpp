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
    _startedAt(),
    _duration(duration)
{
    _timer.setSingleShot(true);
    _timer.setInterval(duration);
    connect(&_timer, SIGNAL(timeout()), this, SIGNAL(done()));
}

SQPerspectiveSwitcher::~SQPerspectiveSwitcher()
{

}

void SQPerspectiveSwitcher::start()
{
    Q_ASSERT(_startedAt.isNull());
    sqMatrixCopy(_projectionMatrix, _startPerspective->projectionMatrix());
    _startedAt = QDateTime::currentDateTime();
    _timer.start();
}

void SQPerspectiveSwitcher::reverse()
{
    SQPerspective* temp = _endPerspective;
    _endPerspective = _startPerspective;
    _startPerspective = temp;

    if (_timer.isActive())
    {
        _timer.stop();
        int e = elapsedTime();
        _timer.setInterval(e);
        _startedAt = QDateTime::currentDateTime().addMSecs(e - _duration);
        _timer.start();
    }
}

void SQPerspectiveSwitcher::setRatio(GLfloat ratio)
{

}

void SQPerspectiveSwitcher::activate()
{

}

void SQPerspectiveSwitcher::deactivate()
{

}
