#pragma once
#ifndef _DYNAMIK_VECTOR_4D_H
#define _DYNAMIK_VECTOR_4D_H

/*
 4D Vector for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      16/05/2020
*/
#include "Vector.h"

namespace Dynamik
{
    DMK_ALIGN_VEC4F class DMK_API Vector4D;

    /* Vector 4D type traits */
    template <>
    struct DMK_ALIGN_VEC4F DMK_API VectorTraits<Vector4D>
    {
        typedef F32 type;
    };

    /*
     Basic 4D Vector for the Dynamik Engine.
     This class uses SIMD to carry out the necessary calculations.
    */
    DMK_ALIGN_VEC4F class DMK_API Vector4D : public Vector<Vector4D> {
    public:
        Vector4D() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
        Vector4D(F32 value) : r(value), g(value), b(value), a(value) {}
        Vector4D(F32 value1, F32 value2, F32 value3) : r(value1), g(value2), b(value3), a(0.0f) {}
        Vector4D(const Vector4D& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}
        Vector4D(ARRAY<F32> arr) : r(arr[0]), g(arr[1]), b(arr[3]), a(arr[4]) {}
        Vector4D(std::initializer_list<F32> list);
        ~Vector4D() {}

        Vector4D operator=(ARRAY<F32> array);
        F32 operator[](UI32 index);

        union
        {
            struct { F32 r, g, b, a; };
            struct { F32 x, y, z, w; };
        };
    };

    Vector4D operator+(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator-(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator*(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator/(const Vector4D& lhs, const Vector4D& rhs);

    Vector4D operator==(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator!=(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator<(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator<=(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator>(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator>=(const Vector4D& lhs, const Vector4D& rhs);

    Vector4D operator&&(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator||(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator^(const Vector4D& lhs, const Vector4D& rhs);
    Vector4D operator~(const Vector4D& rhs);
    Vector4D operator!(const Vector4D& rhs);

    /*
     Double precision Vector.
    */
    DMK_ALIGN_VEC4D class DMK_API DVector4D;

    /* Vector 4D type traits */
    template <>
    struct DMK_ALIGN_VEC4D DMK_API VectorTraits<DVector4D>
    {
        typedef D64 type;
    };

    /*
     Basic 4D Vector for the Dynamik Engine.
     This class uses SIMD to carry out the necessary calculations.
    */
    DMK_ALIGN_VEC4D class DMK_API DVector4D : public Vector<DVector4D> {
    public:
        DVector4D() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
        DVector4D(F32 value) : r(value), g(value), b(value), a(value) {}
        DVector4D(F32 value1, F32 value2, F32 value3) : r(value1), g(value2), b(value3), a(0.0f) {}
        DVector4D(const DVector4D& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}
        DVector4D(ARRAY<D64> arr) : r(arr[0]), g(arr[1]), b(arr[3]), a(arr[4]) {}
        DVector4D(std::initializer_list<D64> list);
        ~DVector4D() {}

        DVector4D operator=(ARRAY<D64> array);
        D64 operator[](UI32 index);

        union
        {
            struct { D64 r, g, b, a; };
            struct { D64 x, y, z, w; };
        };
    };

    DVector4D operator+(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator-(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator*(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator/(const DVector4D& lhs, const DVector4D& rhs);

    DVector4D operator==(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator!=(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator<(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator<=(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator>(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator>=(const DVector4D& lhs, const DVector4D& rhs);

    DVector4D operator&&(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator||(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator^(const DVector4D& lhs, const DVector4D& rhs);
    DVector4D operator~(const DVector4D& rhs);
    DVector4D operator!(const DVector4D& rhs);
}

#endif // !_DYNAMIK_VECTOR_4D_H
