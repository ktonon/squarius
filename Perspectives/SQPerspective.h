/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPERSPECTIVE_H
#define SQPERSPECTIVE_H

#include <QtCore>
#include "SQOpenGL.h"
#include "SQTypes.h"


class SQPerspective : public QObject
{
    Q_OBJECT
public:
    explicit SQPerspective(int maxDimension, QObject *parent = 0);
    virtual ~SQPerspective();

    /** @name Getters */
    /** @{ */

    /**
     * @brief Return the engines projection matrix.
     * @return A 4x4 projection matrix
     */
    virtual QMatrix4x4 projectionMatrix() { return _projectionMatrix; }

    /**
     * @brief Maximum number of cells being rendered by this perspective
     */
    int maxDimension() const { return _maxDimension; }
    /** @} */


    /**
     * @brief Creates a projection matrix using the new ratio.
     * @param ratio
     */
    virtual void setRatio(GLfloat ratio) = 0;

    virtual void setShape(int w, int h) = 0;

public slots:
    /**
     * @brief Make the engine active.
     */
    virtual void activate();

    /**
     * @brief Make the engine inactive.
     */
    virtual void deactivate();

signals:
    void activated();
    void deactivated();

protected:
    QMatrix4x4 _projectionMatrix;
    int _maxDimension;

};

#endif // SQPERSPECTIVE_H
