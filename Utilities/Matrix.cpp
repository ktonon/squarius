/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "Matrix.h"

void sqMatrixCopy(SQMatrix dest, SQMatrix src)
{
    for (int i = 0; i < 16; i++)
        dest[i] = src[i];
}
