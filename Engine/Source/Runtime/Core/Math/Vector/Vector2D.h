// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_VECTOR_2D_H
#define _DYNAMIK_MATH_VECTOR_2D_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "Vector.h"

namespace Dynamik
{
    class DMK_API Vector2D;

    /* Vector 2D type traits */
    template <>
    struct DMK_API VectorTraits<Vector2D>
    {
        typedef D64 type;
    };

    /*
     2D double Vector class for the Dynamik Engine
    */
    class Vector2D : public Vector<Vector2D>
    {
    public:
        Vector2D() : x(0.0), y(0.0) {}
        Vector2D(D64 value) : x(value), y(value) {}
        Vector2D(D64 value1, D64 value2) : x(value1), y(value2) {}
        Vector2D(std::initializer_list<D64> list);
        ~Vector2D() {}

        Vector2D operator=(const std::initializer_list<D64>& list);
        D64& operator[](UI32 index) const;

    public:
        union
        {
            struct { D64 x, y; };
            struct { D64 a, b; };
            struct { D64 width, height; };
        };
    };

    Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
    Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);
    Vector2D operator*(const Vector2D& lhs, const Vector2D& rhs);
    Vector2D operator/(const Vector2D& lhs, const Vector2D& rhs);

    B1 operator==(const Vector2D& lhs, const Vector2D& rhs);
    B1 operator!=(const Vector2D& lhs, const Vector2D& rhs);
    B1 operator<(const Vector2D& lhs, const Vector2D& rhs);
    B1 operator<=(const Vector2D& lhs, const Vector2D& rhs);
    B1 operator>(const Vector2D& lhs, const Vector2D& rhs);
    B1 operator>=(const Vector2D& lhs, const Vector2D& rhs);

    B1 operator&&(const Vector2D& lhs, const Vector2D& rhs);
    B1 operator||(const Vector2D& lhs, const Vector2D& rhs);
    B1 operator^(const Vector2D& lhs, const Vector2D& rhs);
    B1 operator~(const Vector2D& rhs);
    B1 operator!(const Vector2D& rhs);
}

#endif // !_DYNAMIK_VECTOR_2D_H
