/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#pragma once
#include "Perspectives/SQPerspective.h"

class IPerspectiveProvider
{
public:
    virtual SQPerspective *perspective() const = 0;
};
