#include "dmkafx.h"
#include "Vector3F.h"

#include "../SIMD/SIMDFunctions.h"

namespace Dynamik 
{
    Vector3F::Vector3F(std::initializer_list<F32> list)
    {
        SIMD128 _simd;
        _simd.load(list.begin());
        *this = _simd.toVec3F();
    }

    Vector3F Vector3F::operator=(const std::initializer_list<F32>& list)
    {
        SIMD128 _simd;
        _simd.load(list.begin());
        *this = _simd.toVec3F();

        w = 0.0f;
        return *this;
    }

    F32& Vector3F::operator[](UI32 index) const
    {
        return ((F32*)this)[index];
    }

	void Vector3F::load(F32* address)
	{
        SIMD128 _simd;
        _simd.load(address);
        *this = _simd.toVec3F();
	}

    Vector3F operator+(const Vector3F& lhs, const Vector3F& rhs)
    {
        return SIMDFunctions::addVector128F(lhs, rhs).toVec3F();
    }

    Vector3F operator-(const Vector3F& lhs, const Vector3F& rhs)
    {
        return SIMDFunctions::subVector128F(lhs, rhs).toVec3F();
    }

    Vector3F operator*(const Vector3F& lhs, const Vector3F& rhs)
    {
        return SIMDFunctions::mulVector128F(lhs, rhs).toVec3F();
    }

    Vector3F operator/(const Vector3F& lhs, const Vector3F& rhs)
    {
        return SIMDFunctions::divVector128F(lhs, rhs).toVec3F();
    }

    B1 operator==(const Vector3F& lhs, const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::isEqualVector128F(lhs, rhs).toVec3F();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator!=(const Vector3F& lhs, const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::isNotEqualVector128F(lhs, rhs).toVec3F();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator<(const Vector3F& lhs, const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::isLessThanVector128F(lhs, rhs).toVec3F();
        return ((vec.x != 0) || (vec.y != 0) && (vec.z != 0) || (vec.w != 0));
    }

    B1 operator<=(const Vector3F& lhs, const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::isLessThanOrEqualVector128F(lhs, rhs).toVec3F();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator>(const Vector3F& lhs, const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::isGraterThanVector128F(lhs, rhs).toVec3F();
        return ((vec.x != 0) || (vec.y != 0) || (vec.z != 0) || (vec.w != 0));
    }

    B1 operator>=(const Vector3F& lhs, const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::isGraterThanOrEqualVector128F(lhs, rhs).toVec3F();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator&&(const Vector3F& lhs, const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::andVector128F(lhs, rhs).toVec3F();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator||(const Vector3F& lhs, const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::orVector128F(lhs, rhs).toVec3F();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator^(const Vector3F& lhs, const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::orVector128F(lhs, rhs).toVec3F();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator~(const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::orVector128F(rhs, -1).toVec3F();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator!(const Vector3F& rhs)
    {
        auto vec = SIMDFunctions::notVector128F(rhs, 0).toVec3F();
        return ((vec.x == 0) && (vec.y == 0) && (vec.z == 0) && (vec.w == 0));
    }
}