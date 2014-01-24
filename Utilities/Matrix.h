/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "SQTypes.h"

/**
 * @brief Copy the contents of src into dest
 * @param dest A destination matrix
 * @param src A source matrix
 * @note Both matrices must already be allocated
 */
void sqMatrixCopy(SQMatrix dest, SQMatrix src);

#endif // MATRIX_H
