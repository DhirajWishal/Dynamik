#include "dmkafx.h"
#include "Vector3D.h"

#include "SIMD/SIMDFunctions.h"

namespace Dynamik
{
    Vector3D::Vector3D(std::initializer_list<F32> list)
    {
        SIMD128 _simd;
        _simd.load(list.begin());
        *this = _simd.toVec3();
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
        return SIMDFunctions::addVector128(lhs, rhs).toVec3();
    }

    Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::subVector128(lhs, rhs).toVec3();
    }
    
    Vector3D operator*(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::mulVector128(lhs, rhs).toVec3();
    }
    
    Vector3D operator/(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::divVector128(lhs, rhs).toVec3();
    }
    
    Vector3D operator==(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isEqualVector128(lhs, rhs).toVec3();
    }
    
    Vector3D operator!=(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isNotEqualVector128(lhs, rhs).toVec3();
    }
   
    Vector3D operator<(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isLessThanVector128(lhs, rhs).toVec3();
    }
    
    Vector3D operator<=(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isLessThanOrEqualVector128(lhs, rhs).toVec3();
    }
    
    Vector3D operator>(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isGraterThanVector128(lhs, rhs).toVec3();
    }
    
    Vector3D operator>=(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::isGraterThanOrEqualVector128(lhs, rhs).toVec3();
    }
    
    Vector3D operator&&(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::andVector128(lhs, rhs).toVec3();
    }
    
    Vector3D operator||(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::orVector128(lhs, rhs).toVec3();
    }

    Vector3D operator^(const Vector3D& lhs, const Vector3D& rhs)
    {
        return SIMDFunctions::orVector128(lhs, rhs).toVec3();
    }

    Vector3D operator~(const Vector3D& rhs)
    {
        return SIMDFunctions::orVector128(rhs, -1).toVec3();
    }
    
    Vector3D operator!(const Vector3D& rhs)
    {
        return SIMDFunctions::notVector128(rhs, 0).toVec3();
    }
}