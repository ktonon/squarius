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

#include "SQTower.h"

SQTower::SQTower(const QDomElement &elem, Type type) :
    QObject(0),
    _type(type),
    _cost(elem.attribute("cost").toFloat())
{
}

SQTower::~SQTower()
{
}

bool operator<(const SQTower::SP &a, const SQTower::SP &b)
{
    return ((int)a->type()) < ((int)b->type());
}
