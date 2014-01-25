/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPERSPECTIVESWITCHER_H
#define SQPERSPECTIVESWITCHER_H

#include <QtCore>
#include "SQPerspective.h"

/**
 * @brief Animates the transition from one perspective to another
 */
class SQPerspectiveSwitcher : public SQPerspective
{
    Q_OBJECT
public:
    static const int DEFAULT_DURATION;

    /**
     * @brief Create a new perspective switching animation
     * @param start The perspective to start with
     * @param end The perspective to end with
     * @param duration The duration of the animation in milliseconds
     * @param parent Qt parent object
     */
    explicit SQPerspectiveSwitcher(SQPerspective* start, SQPerspective* end, int duration = DEFAULT_DURATION, QObject *parent = 0);
    virtual ~SQPerspectiveSwitcher();

    /** @name Getters */
    /** @{ */
    SQPerspective* startPerspective() const { return _startPerspective; }
    SQPerspective* endPerspective() const { return _endPerspective; }

    /**
     * @brief The time remaining in the animation
     * @return A time value measured in milliseconds
     */
    int elapsedTime() const { return _startedAt.msecsTo(QDateTime::currentDateTime()); }
    /** @} */

    /** @name SQPerspective interface */
    /** @{ */
    virtual const GLfloat* projectionMatrix();
    virtual void setRatio(GLfloat ratio);
public slots:
    virtual void activate();
    /** @} */

private:
    SQPerspective* _startPerspective;
    SQPerspective* _endPerspective;
    QTimer _timer;
    QDateTime _startedAt;
    GLfloat _ratio;
};

#endif // SQPERSPECTIVESWITCHER_H
