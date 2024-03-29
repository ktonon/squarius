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

#include "SQWave.h"

SQWave::List SQWave::create(const QDomDocument &doc)
{
    List waves;
    QDomNodeList nodes = doc.elementsByTagName("wave");
    for (int i=0, n=nodes.count(); i<n; i++)
        waves << create(nodes.at(i).toElement());
    qSort(waves);
    foreach (const SP &wave, waves)
        qDebug() << wave->toString();
    return waves;
}

SQWave::SQWave(const QDomElement &elem) :
    QObject(0),
    _swarmId(elem.attribute("swarmId").toInt()),
    _sourceId(elem.attribute("sourceId").toInt()),
    _strength(elem.attribute("strength").toFloat()),
    _time(elem.attribute("time").toFloat() * 1000)
{
}

SQWave::~SQWave()
{

}

bool operator<(const SQWave::SP &a, const SQWave::SP &b)
{
    return a->time() < b->time();
}
