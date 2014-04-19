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

#ifndef SQPANGESTURERECOGNIZER_H
#define SQPANGESTURERECOGNIZER_H

#include <QtCore>
#include <QGestureRecognizer>
#include <QGesture>

class SQPanGesture;

class SQPanGestureRecognizer : public QGestureRecognizer
{
public:
    explicit SQPanGestureRecognizer();
    virtual ~SQPanGestureRecognizer();

    static void registerMe();
    static Qt::GestureType recognizerId() { return _id; }

    virtual QGesture *create(QObject *target);
    virtual Result recognize(QGesture *state, QObject *watched, QEvent *event);
    virtual void reset(QGesture *state);

private:
    void update(SQPanGesture *q, const QPointF &pos);
    static Qt::GestureType _id;

};

class SQPanGesture : public QGesture
{
public:
    SQPanGesture(QObject *parent = 0) : QGesture(parent) {}
    virtual ~SQPanGesture() {}

    qreal acceleration() const { return 0.0; /* TODO: fix me */ }
    QPointF delta() const { return _currentPos - _lastPos; }
    QPointF lastOffset() const { return _lastPos - _startPos; }
    QPointF offset() const { return _currentPos - _startPos; }

private:
    QPointF _startPos;
    QPointF _lastPos;
    QPointF _currentPos;
    bool _triggered;
    bool _suspected;

    friend class SQPanGestureRecognizer;
};

#endif // SQPANGESTURERECOGNIZER_H
