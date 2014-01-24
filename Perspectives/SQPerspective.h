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
#include <QSharedPointer>

typedef GLfloat* SQProjectionMatrix;

class SQPerspective : public QObject
{
    Q_OBJECT
public:
    explicit SQPerspective(QObject *parent = 0);
    virtual ~SQPerspective();

    /**
     * @brief Return the engines projection matrix.
     * @return A 4x4 projection matrix
     */
    SQProjectionMatrix projectionMatrix() { return _projectionMatrix; }

    /**
     * @brief Creates a projection matrix using the new ratio.
     * @param ratio
     */
    virtual void setRatio(GLfloat ratio) = 0;

    /**
     * @brief Render the model view.
     */
    virtual void renderModel() = 0;

    /**
     * @brief Make the engine active.
     */
    virtual void activate() = 0;

    /**
     * @brief Make the engine inactive.
     */
    virtual void deactivate() = 0;

    /**
     * @brief Update orientation
     * @param modelView The model view matrix
     */
    virtual void updateOrientation(GLfloat const* modelView) = 0;

signals:

public slots:

private:
    SQProjectionMatrix _projectionMatrix;

};

#endif // PERSPECTIVE_H
