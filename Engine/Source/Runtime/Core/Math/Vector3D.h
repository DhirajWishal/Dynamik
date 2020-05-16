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
    DMK_ALIGN class DMK_API Vector3D;

    template <>
    struct DMK_ALIGN DMK_API VectorTraits<Vector3D>
    {
        typedef F32 type;
    };

    /*
     Basic 3D Vector for the Dynamik Engine.
     This class uses SIMD to carry out the necessary calculations.
    */
    DMK_ALIGN class DMK_API Vector3D : public Vector<Vector3D> {
    public:
        Vector3D() {}
        Vector3D(F32 value) : x(value), y(value), z(value), a(value) {}
        Vector3D(F32 value1, F32 value2, F32 value3) : x(value1), y(value2), z(value3), a(0.0f) {}
        Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z), a(other.a) {}
        Vector3D(ARRAY<F32> arr) : x(arr[0]), y(arr[1]), z(arr[3]), a(arr[4]) {}
        Vector3D(std::initializer_list<F32> list);
        ~Vector3D() {}

        Vector3D operator=(ARRAY<F32> array);
        F32 operator[](UI32 index);

        F32 x = 0.0f;
        F32 y = 0.0f;
        F32 z = 0.0f;
        F32 a = 0.0f;
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
}

#endif // !_DYNAMIK_MATH_VECTOR_3_H
