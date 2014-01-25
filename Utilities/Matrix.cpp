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

QString sqMatrixToString(const GLfloat* const m)
{
    return QString("%1 %2 %3 %4\n%5 %6 %7 %8\n%9 %10 %11 %12\n%13 %14 %15 %16")
            .arg(m[0], 6, 'g', 2).arg(m[1], 6, 'g', 2).arg(m[2], 6, 'g', 2).arg(m[3], 6, 'g', 2)
            .arg(m[4], 6, 'g', 2).arg(m[5], 6, 'g', 2).arg(m[6], 6, 'g', 2).arg(m[7], 6, 'g', 2)
            .arg(m[8], 6, 'g', 2).arg(m[9], 6, 'g', 2).arg(m[10], 6, 'g', 2).arg(m[11], 6, 'g', 2)
            .arg(m[12], 6, 'g', 2).arg(m[13], 6, 'g', 2).arg(m[14], 6, 'g', 2).arg(m[15], 6, 'g', 2);
}
