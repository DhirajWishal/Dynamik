#pragma once
#ifndef _DYNAMIK_MATH_VECTOR_3D_H
#define _DYNAMIK_MATH_VECTOR_3D_H

/*
 3D Vector for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "Vector.h"

namespace Dynamik
{
    DMK_ALIGN_VEC3F class DMK_API Vector3D;

    /* Vector 3D type traits */
    template <>
    struct DMK_ALIGN_VEC3F DMK_API VectorTraits<Vector3D>
    {
        typedef F32 type;
    };

    /*
     Basic 3D Vector for the Dynamik Engine.
     This class uses SIMD to carry out the necessary calculations.
    */
    DMK_ALIGN_VEC3F class DMK_API Vector3D : public Vector<Vector3D> {
    public:
        Vector3D() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        Vector3D(F32 value) : x(value), y(value), z(value), a(value) {}
        Vector3D(F32 value1, F32 value2, F32 value3) : x(value1), y(value2), z(value3), a(0.0f) {}
        Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z), a(other.a) {}
        Vector3D(ARRAY<F32> arr) : x(arr[0]), y(arr[1]), z(arr[3]), a(arr[4]) {}
        Vector3D(std::initializer_list<F32> list);
        ~Vector3D() {}

        Vector3D operator=(ARRAY<F32> array);
        F32 operator[](UI32 index);

        union
        {
            struct { F32 x, y, z, w; };
            struct { F32 r, g, b, a; };
        };
    };

    Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator*(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator/(const Vector3D& lhs, const Vector3D& rhs);

    Vector3D operator==(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator!=(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator<(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator<=(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator>(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator>=(const Vector3D& lhs, const Vector3D& rhs);

    Vector3D operator&&(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator||(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator^(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator~(const Vector3D& rhs);
    Vector3D operator!(const Vector3D& rhs);

    /*
     Double precision Vector.
    */

    DMK_ALIGN_VEC3D class DMK_API DVector3D;

    /* Vector 3D type traits */
    template <>
    struct DMK_ALIGN_VEC3D DMK_API VectorTraits<DVector3D>
    {
        typedef D64 type;
    };

    /*
     Double precision 3D vector.
    */
    DMK_ALIGN_VEC3D class DMK_API DVector3D : public Vector<DVector3D> {
    public:
        DVector3D() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        DVector3D(D64 value) : x(value), y(value), z(value), a(value) {}
        DVector3D(D64 value1, D64 value2, D64 value3) : x(value1), y(value2), z(value3), a(0.0) {}
        DVector3D(const DVector3D& other) : x(other.x), y(other.y), z(other.z), a(other.a) {}
        DVector3D(ARRAY<D64> arr) : x(arr[0]), y(arr[1]), z(arr[3]), a(arr[4]) {}
        DVector3D(std::initializer_list<D64> list);
        ~DVector3D() {}

        DVector3D operator=(ARRAY<D64> array);
        D64 operator[](UI32 index);

        union
        {
            struct { D64 x, y, z, w; };
            struct { D64 r, g, b, a; };
        };
    };

    DVector3D operator+(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator-(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator*(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator/(const DVector3D& lhs, const DVector3D& rhs);

    DVector3D operator==(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator!=(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator<(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator<=(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator>(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator>=(const DVector3D& lhs, const DVector3D& rhs);

    DVector3D operator&&(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator||(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator^(const DVector3D& lhs, const DVector3D& rhs);
    DVector3D operator~(const DVector3D& rhs);
    DVector3D operator!(const DVector3D& rhs);
}

#endif // !_DYNAMIK_MATH_VECTOR_3_H
