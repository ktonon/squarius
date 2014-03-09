/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQPOINT_H
#define SQPOINT_H

#include <QString>
#include "SQVector.h"


template <typename T> class SQPoint {
public:
    SQPoint();
    SQPoint(SQPoint<T> const &other);
    SQPoint(T x, T y, T z);
    ~SQPoint();

    T getComponent(int index) const {return index == 0 ? x : (index == 1 ? y : z);}
    void setComponent(int index, T value) {
        switch (index) {
            case 0:
                x = value;
                break;
            case 1:
                y = value;
                break;
            case 2:
                z = value;
                break;
            default:
                break;
        }
    }

    // ARITHMETIC
    SQPoint<T> operator+(SQVector<T> const &m) const;
    SQPoint<T> operator-(SQVector<T> const &m) const;
    SQVector<T> operator-(SQPoint<T> const &other) const;

    // IN-PLACE ARITHMETIC
    void operator+=(SQVector<T> const &m);
    void operator-=(SQVector<T> const &m);

    // UTILITY
    QString toString(void) const;

    // DATA
    T x, y, z;
};


typedef SQPoint<int> SQPointI;
typedef SQPoint<float> SQPointF;

template <typename T> SQPoint<T>::SQPoint():x(0), y(0), z(0) {}
template <typename T> SQPoint<T>::SQPoint(SQPoint<T> const &other): x(other.x), y(other.y), z(other.z) {}
template <typename T> SQPoint<T>::SQPoint(T x, T y, T z):x(x), y(y), z(z) {}
template <typename T> SQPoint<T>::~SQPoint() {}

template <typename T> SQPoint<T> SQPoint<T>::operator+(SQVector<T> const &m) const {
    return SQPoint<T>(x + m.u, y + m.v, z + m.w);
}

template <typename T> SQPoint<T> SQPoint<T>::operator-(SQVector<T> const &m) const {
    return SQPoint<T>(x - m.u, y - m.v, z - m.w);
}

template <typename T> SQVector<T> SQPoint<T>::operator-(SQPoint<T> const &other) const {
    return SQVector<T>(x - other.x, y - other.y, z - other.z);
}

template <typename T> void SQPoint<T>::operator+=(SQVector<T> const &m) {
    x += m.u; y += m.v; z += m.w;
}

template <typename T> void SQPoint<T>::operator-=(SQVector<T> const &m) {
    x -= m.u; y -= m.v; z -= m.w;
}

template <typename T> QString SQPoint<T>::toString(void) const {
    return QString("(%d, %d, %d)").arg(x).arg(y).arg(z);
}

#endif // SQPOINT_H
