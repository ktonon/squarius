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

#include "SQSwarm.h"

SQSwarm::SQSwarm(const QDomElement &parentElem) :
    QObject(0),
    _id(parentElem.attribute("id").toInt()),
    _crawlers()
{
    foreach (SQCrawler::Type type, SQCrawler::types())
    {
        QDomNodeList nodes = parentElem.elementsByTagName(SQCrawler::typeToString(type));
        for (int i=0, n=nodes.count(); i<n; i++)
        {
            QDomElement elem = nodes.at(i).toElement();
            qint64 time = elem.attribute("time").toFloat() * 1000.0f;
            _crawlers << SQCrawler::create(time, type);
        }
    }
    qSort(_crawlers);
}

SQSwarm::~SQSwarm()
{

}
