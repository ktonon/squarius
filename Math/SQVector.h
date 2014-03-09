/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQVECTOR_H
#define SQVECTOR_H

#include <QString>
#include "SQPoint.h"


template <typename T>
class SQVector {
public:
    SQVector();
    SQVector(SQVector<T> const &other);
    SQVector(T u, T v, T w);
    ~SQVector();

    // ARITHMETIC
    SQVector<T> operator-(void) const;
    SQVector<T> operator+(SQVector<T> const &other) const;
    SQVector<T> operator-(SQVector<T> const &other) const;
    SQVector<T> operator*(T scalar) const;
    T dot(SQVector<T> const &other) const;
    SQVector<T> cross(SQVector<T> const &other) const;
    float norm(void) const;

    // IN-PLACE ARITHMETIC
    void operator+=(SQVector<T> const &other);
    void operator-=(SQVector<T> const &other);
    void operator*=(T scalar);

    // COMPARISSON
    bool operator==(SQVector<T> const &other) const;
    bool operator!=(SQVector<T> const &other) const;

    // UTILITY
    QString toString(void) const;

    // DATA
    T u, v, w;

    // CONSTANTS
    static SQVector<T> i(void) { return SQVector<T>(1, 0, 0); }
    static SQVector<T> j(void) { return SQVector<T>(0, 1, 0); }
    static SQVector<T> k(void) { return SQVector<T>(0, 0, 1); }
};

template <typename T> SQVector<T> operator*(T scalar, SQVector<T> m);

typedef SQVector<int> SQVectorI;
typedef SQVector<float> SQVectorF;

template <typename T> SQVector<T>::SQVector(): u(1), v(0), w(0) {}
template <typename T> SQVector<T>::SQVector(SQVector<T> const &other): u(other.u), v(other.v), w(other.w) {}
template <typename T> SQVector<T>::SQVector(T u, T v, T w): u(u), v(v), w(w) {}
template <typename T> SQVector<T>::~SQVector() {}

template <typename T> SQVector<T> SQVector<T>::operator-(void) const {
    return SQVector<T>(-u, -v, -w);
}

template <typename T> SQVector<T> SQVector<T>::operator+(SQVector<T> const &other) const {
    return SQVector<T>(u + other.u, v + other.v, w + other.w);
}

template <typename T> SQVector<T> SQVector<T>::operator-(SQVector<T> const &other) const {
    return SQVector<T>(u - other.u, v - other.v, w - other.w);
}

template <typename T> SQVector<T> SQVector<T>::operator*(T scalar) const {
    return SQVector<T>(u * scalar, v * scalar, w * scalar);
}

template <typename T> T SQVector<T>::dot(SQVector<T> const &other) const {
    return u * other.u + v * other.v + w * other.w;
}

template <typename T> SQVector<T> SQVector<T>::cross(SQVector<T> const &other) const {
    return SQVector<T>(v * other.w - w * other.v, w * other.u - u * other.w, u * other.v - v * other.u);
}

template <typename T> float SQVector<T>::norm(void) const {
    return (float)sqrt(u * u + v * v + w * w);
}

template <typename T> SQVector<T> operator*(T scalar, SQVector<T> m) {
    return SQVector<T>(m.u * scalar, m.v * scalar, m.w * scalar);
}

template <typename T> void SQVector<T>::operator+=(SQVector<T> const &other) {
    u += other.u; v += other.v; w += other.w;
}

template <typename T> void SQVector<T>::operator-=(SQVector<T> const &other) {
    u -= other.u; v -= other.v; w -= other.w;
}

template <typename T> void SQVector<T>::operator*=(T scalar) {
    u *= scalar; v *= scalar; w *= scalar;
}

template <typename T> bool SQVector<T>::operator==(SQVector<T> const &other) const {
    return u == other.u && v == other.v && w == other.w;
}

template <typename T> bool SQVector<T>::operator!=(SQVector<T> const &other) const {
    return u != other.u || v != other.v || w != other.w;
}

template <typename T> QString SQVector<T>::toString(void) const {
    return QString("(%d, %d, %d)").arg(u).arg(v).arg(w);
}

#endif // SQVECTOR_H
