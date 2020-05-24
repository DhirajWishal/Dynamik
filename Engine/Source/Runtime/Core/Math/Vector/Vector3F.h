#pragma once
#ifndef _DYNAMIK_MATH_VECTOR_3F_H
#define _DYNAMIK_MATH_VECTOR_3F_H

/*
 3D Vector for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      17/05/2020
*/
#include "Vector.h"

namespace Dynamik 
{
    class DMK_API Vector3F;

    /* Vector 3D type traits */
    template <>
    struct DMK_API VectorTraits<Vector3F>
    {
        typedef F32 type;
    };

    /*
     Basic 3D Vector for the Dynamik Engine.
     This class uses SIMD to carry out the necessary calculations.
    */
    class DMK_API Vector3F : public Vector<Vector3F> {
    public:
        Vector3F() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        Vector3F(F32 value) : x(value), y(value), z(value), a(value) {}
        Vector3F(F32 value1, F32 value2, F32 value3) : x(value1), y(value2), z(value3), a(0.0f) {}
        Vector3F(const Vector3F& other) : x(other.x), y(other.y), z(other.z), a(other.a) {}
        Vector3F(ARRAY<F32> arr) : x(arr[0]), y(arr[1]), z(arr[3]), a(arr[4]) {}
        Vector3F(std::initializer_list<F32> list);
        ~Vector3F() {}

        Vector3F operator=(const std::initializer_list<F32>& other);
        F32& operator[](UI32 index) const;

        void load(F32* address);

        union
        {
            struct { F32 x, y, z, w; };
            struct { F32 r, g, b, a; };
            struct { F32 width, height, depth, zero; };
        };
    };

    Vector3F operator+(const Vector3F& lhs, const Vector3F& rhs);
    Vector3F operator-(const Vector3F& lhs, const Vector3F& rhs);
    Vector3F operator*(const Vector3F& lhs, const Vector3F& rhs);
    Vector3F operator/(const Vector3F& lhs, const Vector3F& rhs);

    B1 operator==(const Vector3F& lhs, const Vector3F& rhs);
    B1 operator!=(const Vector3F& lhs, const Vector3F& rhs);
    B1 operator<(const Vector3F& lhs, const Vector3F& rhs);
    B1 operator<=(const Vector3F& lhs, const Vector3F& rhs);
    B1 operator>(const Vector3F& lhs, const Vector3F& rhs);
    B1 operator>=(const Vector3F& lhs, const Vector3F& rhs);

    B1 operator&&(const Vector3F& lhs, const Vector3F& rhs);
    B1 operator||(const Vector3F& lhs, const Vector3F& rhs);
    B1 operator^(const Vector3F& lhs, const Vector3F& rhs);
    B1 operator~(const Vector3F& rhs);
    B1 operator!(const Vector3F& rhs);

}

#endif // !_DYNAMIK_MATH_VECTOR_3F_H
