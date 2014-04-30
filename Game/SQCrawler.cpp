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

#include "SQCrawler.h"

SQCrawler::SQCrawler(qint64 time, SQCrawler::Type type) :
    QObject(0),
    _type(type),
    _time(time)
{

}

SQCrawler::~SQCrawler()
{

}

bool operator<(const SQCrawler::SP &a, const SQCrawler::SP &b)
{
    return a->time() < b->time();
}
