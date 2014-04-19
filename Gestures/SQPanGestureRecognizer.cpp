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

#include "SQPanGestureRecognizer.h"
#include <QMouseEvent>
#include <QTouchEvent>
#include <QGraphicsObject>
#include <QWidget>

Qt::GestureType SQPanGestureRecognizer::_id;

SQPanGestureRecognizer::SQPanGestureRecognizer() :
    QGestureRecognizer()
{
}

SQPanGestureRecognizer::~SQPanGestureRecognizer()
{

}

void SQPanGestureRecognizer::registerMe()
{
    _id = QGestureRecognizer::registerRecognizer(new SQPanGestureRecognizer());
}

QGesture *SQPanGestureRecognizer::create(QObject *target)
{
    if (target && target->isWidgetType())
    {
        QWidget *widget = static_cast<QWidget *>(target);
        widget->setAttribute(Qt::WA_AcceptTouchEvents);
    }
    else if (target)
    {
        QGraphicsObject *go = qobject_cast<QGraphicsObject*>(target);
        if (go)
            go->setAcceptTouchEvents(true);
    }
    return new SQPanGesture();
}

QGestureRecognizer::Result SQPanGestureRecognizer::recognize(QGesture *state, QObject *watched, QEvent *event)
{
    SQPanGesture *q = static_cast<SQPanGesture *>(state);
    QGestureRecognizer::Result result = QGestureRecognizer::Ignore;

    const QTouchEvent *ev = static_cast<const QTouchEvent *>(event); // only use ev after checking event->type()
    const QMouseEvent *mouse = static_cast<const QMouseEvent *>(event); // only use ev after checking event->type()

    switch (event->type())
    {
    case QEvent::TouchBegin:
        result = QGestureRecognizer::MayBeGesture;
        if (ev->touchPoints().size() == 1)
        {
            QTouchEvent::TouchPoint p1 = ev->touchPoints().first();
            q->_startPos = p1.startPos();
        }
        break;
    case QEvent::MouseButtonPress:
        result = QGestureRecognizer::MayBeGesture;
        if (!q->_suspected)
        {
            q->_startPos = mouse->pos();
            q->_suspected = true;
        }
        break;
    case QEvent::TouchEnd:
    case QEvent::MouseButtonRelease:
        if (q->_triggered)
            result = QGestureRecognizer::FinishGesture;
        else
            result = QGestureRecognizer::CancelGesture;
        break;
    case QEvent::TouchUpdate:
        if (ev->touchPoints().size() == 1)
        {
            QTouchEvent::TouchPoint p1 = ev->touchPoints().first();
            if (p1.pos() != q->_currentPos)
            {
                update(q, p1.pos());
                result = QGestureRecognizer::TriggerGesture;
            }
        }
        break;
    case QEvent::MouseMove:
        if (q->_suspected && mouse->pos() != q->_currentPos)
        {
            update(q, mouse->pos());
            result = QGestureRecognizer::TriggerGesture;
        }
        break;
    default:
        break;
    }
    return result;
}

void SQPanGestureRecognizer::update(SQPanGesture *q, const QPointF &pos)
{
    q->_triggered = true;
    q->_lastPos = q->_currentPos;
    q->_currentPos = pos;
    if (q->_lastPos.isNull())
        q->_lastPos = q->_currentPos;
}

void SQPanGestureRecognizer::reset(QGesture *state)
{
    SQPanGesture *q = static_cast<SQPanGesture *>(state);
    q->_suspected = false;
    q->_triggered = false;
    q->_startPos = QPoint();
    q->_lastPos = QPoint();
    q->_currentPos = QPoint();

    QGestureRecognizer::reset(state);
}
