// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Vector4F.h"

#include "../IncludeSIMD.h"

namespace Dynamik
{
    Vector4F::Vector4F(std::initializer_list<F32> list)
        : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {
        if ((list.size() > 4) || (list.size() < 4))
            DMK_ERROR_BOX("The size of the provided list does not match the current Vector size!");

        DMKMemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(F32));
    }

    Vector4F::Vector4F(const F32* ptr)
        : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {
        DMKMemoryFunctions::moveData(this, (VPTR)ptr, sizeof(F32) * 4);
    }

    Vector4F Vector4F::operator=(const std::initializer_list<F32>& list)
    {
        if ((list.size() > 4) || (list.size() < 4))
            DMK_ERROR_BOX("The size of the provided list does not match the current Vector size!");

        DMKMemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(F32));

        return *this;
    }

    F32& Vector4F::operator[](UI32 index) const
    {
        return ((F32*)this)[index];
    }

    Vector4F::operator F32* () const
    {
        return (F32*)this;
    }

    Vector4F operator+(const Vector4F& lhs, const Vector4F& rhs)
    {
        return (const F32*)&_mm_add_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
    }

    Vector4F operator-(const Vector4F& lhs, const Vector4F& rhs)
    {
        return (const F32*)&_mm_sub_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
    }

    Vector4F operator*(const Vector4F& lhs, const Vector4F& rhs)
    {
        return (const F32*)&_mm_mul_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
    }

    Vector4F operator/(const Vector4F& lhs, const Vector4F& rhs)
    {
        return (const F32*)&_mm_div_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
    }

    Vector4F operator*(const Vector4F& lhs, const F32& value)
    {
        return (const F32*)&_mm_mul_ps(_mm_load_ps(lhs), _mm_load_ps(Vector4F(value)));
    }

    B1 operator==(const Vector4F& lhs, const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_cmpeq_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator!=(const Vector4F& lhs, const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_cmpneq_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator<(const Vector4F& lhs, const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_cmplt_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
        return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
    }

    B1 operator<=(const Vector4F& lhs, const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_cmple_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator>(const Vector4F& lhs, const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_cmpgt_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
        return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
    }

    B1 operator>=(const Vector4F& lhs, const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_cmpge_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator&&(const Vector4F& lhs, const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_and_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator||(const Vector4F& lhs, const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_or_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator^(const Vector4F& lhs, const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_or_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator~(const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_or_ps(_mm_load_ps(rhs), _mm_load_ps(Vector4F(-1.0f)));
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator!(const Vector4F& rhs)
    {
        Vector4F vec = (const F32*)&_mm_or_ps(_mm_load_ps(rhs), _mm_load_ps(Vector4F(0.0f)));
        return ((vec.r == 0) && (vec.g == 0) && (vec.b == 0) && (vec.a == 0));
    }
}