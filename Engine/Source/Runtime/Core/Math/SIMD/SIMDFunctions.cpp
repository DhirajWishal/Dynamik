#include "dmkafx.h"
#include "SIMDFunctions.h"

namespace Dynamik
{
	SIMD128 SIMDFunctions::addVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_add_ps(lhs, rhs);
	}
	
	SIMD128 SIMDFunctions::subVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_sub_ps(lhs, rhs);
	}
	
	SIMD128 SIMDFunctions::mulVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_mul_ps(lhs, rhs);
	}
	
	SIMD128 SIMDFunctions::divVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_div_ps(lhs, rhs);
	}
	
	SIMD128 SIMDFunctions::andVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_and_ps(lhs, rhs);
	}
	
	SIMD128 SIMDFunctions::orVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_or_ps(lhs, rhs);
	}
	
	SIMD128 SIMDFunctions::xorVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_xor_ps(lhs, rhs);
	}
	
	SIMD128 SIMDFunctions::notVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_andnot_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isEqualVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpeq_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isNotEqualVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpneq_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isLessThanVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmplt_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isLessThanOrEqualVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmple_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isGraterThanVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpgt_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isGraterThanOrEqualVector128(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpge_ps(lhs, rhs);
	}
}