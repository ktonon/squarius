/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "Matrix.h"
#include "SQTypes.h"

QString sqMatrixToString(const QMatrix4x4& m)
{
    return QString("%1 %2 %3 %4\n%5 %6 %7 %8\n%9 %10 %11 %12\n%13 %14 %15 %16")
            .arg(m.row(0).x(), 6, 'g', 2).arg(m.row(0).y(), 6, 'g', 2).arg(m.row(0).z(), 6, 'g', 2).arg(m.row(0).w(), 6, 'g', 2)
            .arg(m.row(1).x(), 6, 'g', 2).arg(m.row(1).y(), 6, 'g', 2).arg(m.row(1).z(), 6, 'g', 2).arg(m.row(1).w(), 6, 'g', 2)
            .arg(m.row(2).x(), 6, 'g', 2).arg(m.row(2).y(), 6, 'g', 2).arg(m.row(2).z(), 6, 'g', 2).arg(m.row(2).w(), 6, 'g', 2)
            .arg(m.row(3).x(), 6, 'g', 2).arg(m.row(3).y(), 6, 'g', 2).arg(m.row(3).z(), 6, 'g', 2).arg(m.row(3).w(), 6, 'g', 2)
            ;
}
