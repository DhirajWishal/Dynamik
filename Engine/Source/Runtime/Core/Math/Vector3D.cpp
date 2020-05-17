#include "dmkafx.h"
#include "Vector3D.h"

#include "SIMD/SIMDFunctions.h"

namespace Dynamik
{
	Vector3D::Vector3D(std::initializer_list<D64> list)
	{
		SIMD256 _simd;
		_simd.load(list.begin());
		*this = _simd.toVec3D();
	}

	Vector3D Vector3D::operator=(const std::initializer_list<D64>& list)
	{
		SIMD256 _simd;
		_simd.load(list.begin());
		*this = _simd.toVec3D();

		return *this;
	}

	D64 Vector3D::operator[](UI32 index)
	{
		return ((D64*)this)[index];
	}

	Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs)
	{
		return SIMDFunctions::addVector256D(lhs, rhs).toVec3D();
	}

	Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs)
	{
		return SIMDFunctions::subVector256D(lhs, rhs).toVec3D();
	}

	Vector3D operator*(const Vector3D& lhs, const Vector3D& rhs)
	{
		return SIMDFunctions::mulVector256D(lhs, rhs).toVec3D();
	}

	Vector3D operator/(const Vector3D& lhs, const Vector3D& rhs)
	{
		return SIMDFunctions::divVector256D(lhs, rhs).toVec3D();
	}

    B1 operator==(const Vector3D& lhs, const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::isEqualVector256D(lhs, rhs).toVec3D();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator!=(const Vector3D& lhs, const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::isNotEqualVector256D(lhs, rhs).toVec3D();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator<(const Vector3D& lhs, const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::isLessThanVector256D(lhs, rhs).toVec3D();
        return ((vec.x != 0) || (vec.y != 0) || (vec.z != 0) || (vec.w != 0));
    }

    B1 operator<=(const Vector3D& lhs, const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::isLessThanOrEqualVector256D(lhs, rhs).toVec3D();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator>(const Vector3D& lhs, const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::isGraterThanVector256D(lhs, rhs).toVec3D();
        return ((vec.x != 0) || (vec.y != 0) || (vec.z != 0) || (vec.w != 0));
    }

    B1 operator>=(const Vector3D& lhs, const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::isGraterThanOrEqualVector256D(lhs, rhs).toVec3D();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator&&(const Vector3D& lhs, const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::andVector256D(lhs, rhs).toVec3D();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator||(const Vector3D& lhs, const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::orVector256D(lhs, rhs).toVec3D();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator^(const Vector3D& lhs, const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::orVector256D(lhs, rhs).toVec3D();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator~(const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::orVector256D(rhs, -1).toVec3D();
        return ((vec.x != 0) && (vec.y != 0) && (vec.z != 0) && (vec.w != 0));
    }

    B1 operator!(const Vector3D& rhs)
    {
        auto vec = SIMDFunctions::notVector256D(rhs, 0).toVec3D();
        return ((vec.x == 0) && (vec.y == 0) && (vec.z == 0) && (vec.w == 0));
    }
}