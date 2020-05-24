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
    class DMK_API Vector3D;

    /* Vector 3D type traits */
    template <>
    struct DMK_API VectorTraits<Vector3D>
    {
        typedef D64 type;
    };

    /*
     Double precision 3D vector.
    */
    class DMK_API Vector3D : public Vector<Vector3D> {
    public:
        Vector3D() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        Vector3D(D64 value) : x(value), y(value), z(value), a(value) {}
        Vector3D(D64 value1, D64 value2, D64 value3) : x(value1), y(value2), z(value3), a(0.0) {}
        Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z), a(other.a) {}
        Vector3D(ARRAY<D64> arr) : x(arr[0]), y(arr[1]), z(arr[3]), a(arr[4]) {}
        Vector3D(std::initializer_list<D64> list);
        ~Vector3D() {}

        Vector3D operator=(const std::initializer_list<D64>& list);
        D64& operator[](UI32 index) const;

        union
        {
            struct { D64 x, y, z, w; };
            struct { D64 r, g, b, a; };
            struct { D64 width, height, depth, zero; };
        };
    };

    Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator*(const Vector3D& lhs, const Vector3D& rhs);
    Vector3D operator/(const Vector3D& lhs, const Vector3D& rhs);

    B1 operator==(const Vector3D& lhs, const Vector3D& rhs);
    B1 operator!=(const Vector3D& lhs, const Vector3D& rhs);
    B1 operator<(const Vector3D& lhs, const Vector3D& rhs);
    B1 operator<=(const Vector3D& lhs, const Vector3D& rhs);
    B1 operator>(const Vector3D& lhs, const Vector3D& rhs);
    B1 operator>=(const Vector3D& lhs, const Vector3D& rhs);

    B1 operator&&(const Vector3D& lhs, const Vector3D& rhs);
    B1 operator||(const Vector3D& lhs, const Vector3D& rhs);
    B1 operator^(const Vector3D& lhs, const Vector3D& rhs);
    B1 operator~(const Vector3D& rhs);
    B1 operator!(const Vector3D& rhs);
}

#endif // !_DYNAMIK_MATH_VECTOR_3_H
