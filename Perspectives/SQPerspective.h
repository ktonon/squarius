/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include <QtCore>
#include <QtOpenGL>
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
    const GLfloat* projectionMatrix() const { return _projectionMatrix; }

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

    /**
     * @brief Make the engine active.
     */
    virtual void activate() = 0;

    /**
     * @brief Make the engine inactive.
     */
    virtual void deactivate() = 0;

protected:
    GLfloat _projectionMatrix[SQ_MATRIX_SIZE];
    int _maxDimension;

};

#endif // PERSPECTIVE_H
