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
    static const int DEFAULT_DURATION = 500;

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
    virtual void setRatio(GLfloat ratio);
    virtual void activate();
    virtual void deactivate();
    /** @} */

signals:
    /**
     * @brief The animation is complete
     */
    void done();

public slots:
    /**
     * @brief Start the animation
     */
    void start();

    /**
     * @brief Reverse the direction of the animation
     */
    void reverse();

private:
    SQPerspective* _startPerspective;
    SQPerspective* _endPerspective;
    QTimer _timer;
    QDateTime _startedAt;
    int _duration;
};

#endif // SQPERSPECTIVESWITCHER_H
