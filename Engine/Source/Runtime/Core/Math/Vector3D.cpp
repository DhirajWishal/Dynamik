#include "dmkafx.h"
#include "Vector3D.h"

#include "SIMD/SIMDFunctions.h"

namespace Dynamik
{
    Vector3D::Vector3D(std::initializer_list<F32> list)
    {
        SIMD128 _simd;
        _simd.load(list.begin());
        *this = _simd.toVec3F();
    }

    Vector3D Vector3D::operator=(ARRAY<F32> array)
    {
        x = array[0];
        y = array[1];
        z = array[2];
        a = array[3];

        return *this;
    }
    
    F32 Vector3D::operator[](UI32 index)
    {
        return ((F32*)this)[index];
    }
    
    Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::addVector128F(lhs, rhs).toVec3F();
    }

    Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::subVector128F(lhs, rhs).toVec3F();
    }
    
    Vector3D operator*(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::mulVector128F(lhs, rhs).toVec3F();
    }
    
    Vector3D operator/(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::divVector128F(lhs, rhs).toVec3F();
    }
    
    Vector3D operator==(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isEqualVector128F(lhs, rhs).toVec3F();
    }
    
    Vector3D operator!=(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isNotEqualVector128F(lhs, rhs).toVec3F();
    }
   
    Vector3D operator<(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isLessThanVector128F(lhs, rhs).toVec3F();
    }
    
    Vector3D operator<=(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isLessThanOrEqualVector128F(lhs, rhs).toVec3F();
    }
    
    Vector3D operator>(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isGraterThanVector128F(lhs, rhs).toVec3F();
    }
    
    Vector3D operator>=(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isGraterThanOrEqualVector128F(lhs, rhs).toVec3F();
    }
    
    Vector3D operator&&(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::andVector128F(lhs, rhs).toVec3F();
    }
    
    Vector3D operator||(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::orVector128F(lhs, rhs).toVec3F();
    }

    Vector3D operator^(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::orVector128F(lhs, rhs).toVec3F();
    }

    Vector3D operator~(const Vector3D& rhs)
    {
        return SIMDFunctions::orVector128F(rhs, -1).toVec3F();
    }
    
    Vector3D operator!(const Vector3D& rhs)
    {
        return SIMDFunctions::notVector128F(rhs, 0).toVec3F();
    }

    /* Double precision */
    DVector3D::DVector3D(std::initializer_list<D64> list)
    {
        SIMD256 _simd;
        _simd.load(list.begin());
        *this = _simd.toVec3D();
    }

    DVector3D DVector3D::operator=(ARRAY<D64> array)
    {
        x = array[0];
        y = array[1];
        z = array[2];
        a = array[3];

        return *this;
    }

    D64 DVector3D::operator[](UI32 index)
    {
        return ((D64*)this)[index];
    }

    DVector3D operator+(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::addVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator-(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::subVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator*(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::mulVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator/(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::divVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator==(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::isEqualVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator!=(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::isNotEqualVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator<(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::isLessThanVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator<=(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::isLessThanOrEqualVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator>(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::isGraterThanVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator>=(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::isGraterThanOrEqualVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator&&(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::andVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator||(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::orVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator^(const DVector3D& lhs, const DVector3D& rhs)
    {
        return SIMDFunctions::orVector256D(lhs, rhs).toVec3D();
    }

    DVector3D operator~(const DVector3D& rhs)
    {
        return SIMDFunctions::orVector256D(rhs, -1).toVec3D();
    }

    DVector3D operator!(const DVector3D& rhs)
    {
        return SIMDFunctions::notVector256D(rhs, 0).toVec3D();
    }
}