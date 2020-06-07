#include "dmkafx.h"
#include "Vector4F.h"

#include "../SIMD/SIMDFunctions.h"

namespace Dynamik
{
    Vector4F::Vector4F(std::initializer_list<F32> list)
    {
        if ((list.size() > 4) || (list.size() < 4))
            DMK_ERROR_BOX("The size of the provided list does not match the current Vector size!");

        DMKMemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(F32));
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

    Vector4F operator+(const Vector4F& lhs, const Vector4F& rhs)
    {
        return SIMDFunctions::addVector128F(lhs, rhs).toVec4F();
    }

    Vector4F operator-(const Vector4F& lhs, const Vector4F& rhs)
    {
        return SIMDFunctions::subVector128F(lhs, rhs).toVec4F();
    }

    Vector4F operator*(const Vector4F& lhs, const Vector4F& rhs)
    {
        return SIMDFunctions::mulVector128F(lhs, rhs).toVec4F();
    }

    Vector4F operator/(const Vector4F& lhs, const Vector4F& rhs)
    {
        return SIMDFunctions::divVector128F(lhs, rhs).toVec4F();
    }

    Vector4F operator*(const Vector4F& lhs, const F32& value)
    {
        return SIMDFunctions::mulVector128F(lhs, value).toVec4F();
    }

    B1 operator==(const Vector4F& lhs, const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::isEqualVector128F(lhs, rhs).toVec4F();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator!=(const Vector4F& lhs, const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::isNotEqualVector128F(lhs, rhs).toVec4F();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator<(const Vector4F& lhs, const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::isLessThanVector128F(lhs, rhs).toVec4F();
        return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
    }

    B1 operator<=(const Vector4F& lhs, const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::isLessThanOrEqualVector128F(lhs, rhs).toVec4F();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator>(const Vector4F& lhs, const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::isGraterThanVector128F(lhs, rhs).toVec4F();
        return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
    }

    B1 operator>=(const Vector4F& lhs, const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::isGraterThanOrEqualVector128F(lhs, rhs).toVec4F();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator&&(const Vector4F& lhs, const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::andVector128F(lhs, rhs).toVec4F();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator||(const Vector4F& lhs, const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::orVector128F(lhs, rhs).toVec4F();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator^(const Vector4F& lhs, const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::orVector128F(lhs, rhs).toVec4F();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator~(const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::orVector128F(rhs, -1).toVec4F();
        return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
    }

    B1 operator!(const Vector4F& rhs)
    {
        auto vec = SIMDFunctions::notVector128F(rhs, 0).toVec4F();
        return ((vec.r == 0) && (vec.g == 0) && (vec.b == 0) && (vec.a == 0));
    }
}