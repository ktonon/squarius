/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQPerspectiveSwitcher.h"
#include "Utilities/Matrix.h"

const int SQPerspectiveSwitcher::DEFAULT_DURATION = 250;

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

const GLfloat* SQPerspectiveSwitcher::projectionMatrix()
{
    float k = (float) elapsedTime() / _timer.interval();
    float theta = k * M_PI;
    float ratio = (1.0f - cosf(theta)) / 2.0f;
    theta = ratio * M_PI;
    ratio = (1.0f - cosf(theta)) / 2.0f;
    const GLfloat* a = _startPerspective->projectionMatrix();
    const GLfloat* b = _endPerspective->projectionMatrix();
    for (int i = 0; i < SQ_MATRIX_SIZE; i++)
    {
        _projectionMatrix[i] = a[i] + (b[i] - a[i]) * ratio;
    }
    return _projectionMatrix;
}

void SQPerspectiveSwitcher::setRatio(GLfloat ratio)
{
    _ratio = ratio;
}

void SQPerspectiveSwitcher::activate()
{
    Q_ASSERT(_startedAt.isNull());
    sqMatrixCopy(_projectionMatrix, _startPerspective->projectionMatrix());
    _startedAt = QDateTime::currentDateTime();
    _timer.start();
    SQPerspective::activate();
}
