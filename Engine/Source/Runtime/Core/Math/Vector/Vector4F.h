#pragma once
#ifndef _DYNAMIK_MATH_VECTOR_4F_H
#define _DYNAMIK_MATH_VECTOR_4F_H

/*
 4D Vector for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      17/05/2020
*/
#include "Vector.h"

namespace Dynamik
{
    class DMK_API Vector4F;

    /* Vector 4D type traits */
    template <>
    struct DMK_API VectorTraits<Vector4F>
    {
        typedef F32 type;
    };

    /*
     Basic 4D Vector for the Dynamik Engine.
     This class uses SIMD to carry out the necessary calculations.
    */
    class DMK_API Vector4F : public Vector<Vector4F> {
    public:
        Vector4F() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
        Vector4F(F32 value) : r(value), g(value), b(value), a(value) {}
        Vector4F(F32 value1, F32 value2, F32 value3, F32 value4) : r(value1), g(value2), b(value3), a(value4) {}
        Vector4F(const Vector4F& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}
        Vector4F(ARRAY<F32> arr) : r(arr[0]), g(arr[1]), b(arr[3]), a(arr[4]) {}
        Vector4F(std::initializer_list<F32> list);
        ~Vector4F() {}

        Vector4F operator=(const std::initializer_list<F32>& list);
        F32& operator[](UI32 index) const;

        union
        {
            struct { F32 r, g, b, a; };
            struct { F32 x, y, z, w; };
            struct { F32 width, height, depth, zero; };
        };
    };

    Vector4F operator+(const Vector4F& lhs, const Vector4F& rhs);
    Vector4F operator-(const Vector4F& lhs, const Vector4F& rhs);
    Vector4F operator*(const Vector4F& lhs, const Vector4F& rhs);
    Vector4F operator/(const Vector4F& lhs, const Vector4F& rhs);

    Vector4F operator*(const Vector4F& lhs, const F32& value);

    B1 operator==(const Vector4F& lhs, const Vector4F& rhs);
    B1 operator!=(const Vector4F& lhs, const Vector4F& rhs);
    B1 operator<(const Vector4F& lhs, const Vector4F& rhs);
    B1 operator<=(const Vector4F& lhs, const Vector4F& rhs);
    B1 operator>(const Vector4F& lhs, const Vector4F& rhs);
    B1 operator>=(const Vector4F& lhs, const Vector4F& rhs);

    B1 operator&&(const Vector4F& lhs, const Vector4F& rhs);
    B1 operator||(const Vector4F& lhs, const Vector4F& rhs);
    B1 operator^(const Vector4F& lhs, const Vector4F& rhs);
    B1 operator~(const Vector4F& rhs);
    B1 operator!(const Vector4F& rhs);
}

#endif // !_DYNAMIK_MATH_VECTOR_4F_H
