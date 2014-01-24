/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "Matrix.h"
#include "SQTypes.h"

void sqMatrixCopy(GLfloat* const dest, const GLfloat* const src)
{
    for (int i = 0; i < SQ_MATRIX_SIZE; i++)
        dest[i] = src[i];
}
