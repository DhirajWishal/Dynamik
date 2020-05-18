#pragma once
#ifndef _DYNAMIK_MATH_VECTOR_4D_H
#define _DYNAMIK_MATH_VECTOR_4D_H

/*
 4D Vector for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      16/05/2020
*/
#include "Vector.h"

namespace Dynamik
{
    class DMK_API Vector4D;

    /* Vector 4D type traits */
    template <>
    struct DMK_API VectorTraits<Vector4D>
    {
        typedef D64 type;
    };

    /*
     Basic 4D Vector for the Dynamik Engine.
     This class uses SIMD to carry out the necessary calculations.
    */
    class DMK_API Vector4D : public Vector<Vector4D> {
    public:
        Vector4D() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
        Vector4D(D64 value) : r(value), g(value), b(value), a(value) {}
        Vector4D(D64 value1, D64 value2, D64 value3, D64 value4) : r(value1), g(value2), b(value3), a(value4) {}
        Vector4D(const Vector4D& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}
        Vector4D(ARRAY<D64> arr) : r(arr[0]), g(arr[1]), b(arr[3]), a(arr[4]) {}
        Vector4D(std::initializer_list<D64> list);
        ~Vector4D() {}

        Vector4D operator=(const std::initializer_list<D64>& list);
        D64 operator[](UI32 index);

        union
        {
            struct { D64 r, g, b, a; };
            struct { D64 x, y, z, w; };
        };
    };

    Vector4D operator+(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator-(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator*(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator/(const Vector4D& lhs, const Vector4D& rhs);

    B1 operator==(const Vector4D& lhs, const Vector4D& rhs);
    B1 operator!=(const Vector4D& lhs, const Vector4D& rhs);
    B1 operator<(const Vector4D& lhs, const Vector4D& rhs);
    B1 operator<=(const Vector4D& lhs, const Vector4D& rhs);
    B1 operator>(const Vector4D& lhs, const Vector4D& rhs);
    B1 operator>=(const Vector4D& lhs, const Vector4D& rhs);

    B1 operator&&(const Vector4D& lhs, const Vector4D& rhs);
    B1 operator||(const Vector4D& lhs, const Vector4D& rhs);
    B1 operator^(const Vector4D& lhs, const Vector4D& rhs);
    B1 operator~(const Vector4D& rhs);
    B1 operator!(const Vector4D& rhs);
}

#endif // !_DYNAMIK_VECTOR_4D_H
