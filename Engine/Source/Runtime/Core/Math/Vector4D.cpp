#include "dmkafx.h"
#include "Vector4D.h"

#include "SIMD/SIMDFunctions.h"

namespace Dynamik
{
    Vector4D::Vector4D(std::initializer_list<D64> list)
    {
        SIMD256 _simd;
        _simd.load(list.begin());
        *this = _simd.toVec4D();
    }

    Vector4D Vector4D::operator=(const std::initializer_list<D64>& list)
    {
        SIMD256 _simd;
        _simd.load(list.begin());
        *this = _simd.toVec4D();

        return *this;
    }

    D64 Vector4D::operator[](UI32 index)
    {
        return ((D64*)this)[index];
    }

    Vector4D operator+(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::addVector256D(lhs, rhs).toVec4D();
    }

    Vector4D operator-(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::subVector256D(lhs, rhs).toVec4D();
    }

    Vector4D operator*(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::mulVector256D(lhs, rhs).toVec4D();
    }

    Vector4D operator/(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::divVector256D(lhs, rhs).toVec4D();
    }

    B1 operator==(const Vector4D& lhs, const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::isEqualVector256D(lhs, rhs).toVec4D();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator!=(const Vector4D& lhs, const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::isNotEqualVector256D(lhs, rhs).toVec4D();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator<(const Vector4D& lhs, const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::isLessThanVector256D(lhs, rhs).toVec4D();
        return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
    }

    B1 operator<=(const Vector4D& lhs, const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::isLessThanOrEqualVector256D(lhs, rhs).toVec4D();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator>(const Vector4D& lhs, const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::isGraterThanVector256D(lhs, rhs).toVec4D();
        return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
    }

    B1 operator>=(const Vector4D& lhs, const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::isGraterThanOrEqualVector256D(lhs, rhs).toVec4D();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator&&(const Vector4D& lhs, const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::andVector256D(lhs, rhs).toVec4D();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator||(const Vector4D& lhs, const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::orVector256D(lhs, rhs).toVec4D();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator^(const Vector4D& lhs, const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::orVector256D(lhs, rhs).toVec4D();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator~(const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::orVector256D(rhs, -1).toVec4D();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator!(const Vector4D& rhs)
    {
        auto vec = SIMDFunctions::notVector256D(rhs, 0).toVec4D();
        return ((vec.r == 0) && (vec.g == 0) && (vec.b == 0) && (vec.a == 0));
    }
}