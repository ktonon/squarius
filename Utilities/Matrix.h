/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQMATRIX_H
#define SQMATRIX_H

#include <QtOpenGL>

/**
 * @brief Copy the contents of src into dest
 * @param dest A destination matrix
 * @param src A source matrix
 * @note Both matrices must already be allocated
 */
void sqMatrixCopy(GLfloat* const dest, const GLfloat* const src);

QString sqMatrixToString(const GLfloat* const m);

#endif // SQMATRIX_H
