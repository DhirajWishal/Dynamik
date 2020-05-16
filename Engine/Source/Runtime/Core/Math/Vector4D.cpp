#include "dmkafx.h"
#include "Vector4D.h"

#include "SIMD/SIMDFunctions.h"

namespace Dynamik
{
	Vector4D::Vector4D(std::initializer_list<F32> list)
	{
        SIMD128 _simd;
        _simd.load(list.begin());
        *this = _simd.toVec4F();
	}
	
	Vector4D Vector4D::operator=(ARRAY<F32> array)
	{
        r = array[0];
        g = array[1];
        b = array[2];
        a = array[3];

        return *this;
	}
	
	F32 Vector4D::operator[](UI32 index)
	{
        return ((F32*)this)[index];
	}

    Vector4D operator+(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::addVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator-(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::subVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator*(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::mulVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator/(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::divVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator==(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::isEqualVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator!=(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::isNotEqualVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator<(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::isLessThanVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator<=(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::isLessThanOrEqualVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator>(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::isGraterThanVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator>=(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::isGraterThanOrEqualVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator&&(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::andVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator||(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::orVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator^(const Vector4D& lhs, const Vector4D& rhs)
    {
        return SIMDFunctions::orVector128F(lhs, rhs).toVec4F();
    }

    Vector4D operator~(const Vector4D& rhs)
    {
        return SIMDFunctions::orVector128F(rhs, -1).toVec4F();
    }

    Vector4D operator!(const Vector4D& rhs)
    {
        return SIMDFunctions::notVector128F(rhs, 0).toVec4F();
    }

    /*
     Double precision.
    */
    DVector4D::DVector4D(std::initializer_list<D64> list)
    {
        SIMD256 _simd;
        _simd.load(list.begin());
        *this = _simd.toVec4D();
    }

    DVector4D DVector4D::operator=(ARRAY<D64> array)
    {
        r = array[0];
        g = array[1];
        b = array[2];
        a = array[3];

        return *this;
    }

    D64 DVector4D::operator[](UI32 index)
    {
        return ((D64*)this)[index];
    }

    DVector4D operator+(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::addVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator-(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::subVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator*(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::mulVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator/(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::divVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator==(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::isEqualVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator!=(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::isNotEqualVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator<(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::isLessThanVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator<=(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::isLessThanOrEqualVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator>(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::isGraterThanVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator>=(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::isGraterThanOrEqualVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator&&(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::andVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator||(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::orVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator^(const DVector4D& lhs, const DVector4D& rhs)
    {
        return SIMDFunctions::orVector256D(lhs, rhs).toVec4D();
    }

    DVector4D operator~(const DVector4D& rhs)
    {
        return SIMDFunctions::orVector256D(rhs, -1).toVec4D();
    }

    DVector4D operator!(const DVector4D& rhs)
    {
        return SIMDFunctions::notVector256D(rhs, 0).toVec4D();
    }
}