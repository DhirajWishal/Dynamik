#include "dmkafx.h"
#include "SIMDFunctions.h"

namespace Dynamik
{
	/* ---------- 128 bit operations ---------- */
	SIMD128 SIMDFunctions::addVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_add_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::subVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_sub_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::mulVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_mul_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::divVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_div_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::andVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_and_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::orVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_or_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::xorVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_xor_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::notVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_andnot_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isEqualVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpeq_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isNotEqualVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpneq_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isLessThanVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmplt_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isLessThanOrEqualVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmple_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isGraterThanVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpgt_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isGraterThanOrEqualVector128F(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpge_ps(lhs, rhs);
	}

	SIMD128 SIMDFunctions::addVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_add_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::subVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_sub_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::mulVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_mul_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::divVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_div_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::andVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_and_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::orVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_or_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::xorVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_xor_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::notVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_andnot_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isEqualVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpeq_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isNotEqualVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpneq_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isLessThanVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmplt_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isLessThanOrEqualVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmple_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isGraterThanVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpgt_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isGraterThanOrEqualVector128D(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpge_pd(lhs, rhs);
	}

	SIMD128 SIMDFunctions::addVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_add_epi32(lhs, rhs);
	}

	SIMD128 SIMDFunctions::subVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_sub_epi32(lhs, rhs);
	}

	SIMD128 SIMDFunctions::mulVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_mul_epi32(lhs, rhs);
	}

	SIMD128 SIMDFunctions::divVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_div_epi32(lhs, rhs);
	}

	SIMD128 SIMDFunctions::andVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_and_si128(lhs, rhs);
	}

	SIMD128 SIMDFunctions::orVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_or_si128(lhs, rhs);
	}

	SIMD128 SIMDFunctions::xorVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_xor_si128(lhs, rhs);
	}

	SIMD128 SIMDFunctions::notVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_andnot_si128(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isEqualVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpeq_epi32_mask(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isNotEqualVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpneq_epi32_mask(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isLessThanVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmplt_epi32_mask(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isLessThanOrEqualVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmple_epi32_mask(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isGraterThanVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpgt_epi32_mask(lhs, rhs);
	}

	SIMD128 SIMDFunctions::isGraterThanOrEqualVector128I(SIMD128 lhs, SIMD128 rhs)
	{
		return _mm_cmpge_epi32_mask(lhs, rhs);
	}

	/* ---------- 256 bit operations ---------- */
	SIMD256 SIMDFunctions::addVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_add_ps(lhs, rhs);
	}

	SIMD256 SIMDFunctions::subVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_sub_ps(lhs, rhs);
	}

	SIMD256 SIMDFunctions::mulVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_mul_ps(lhs, rhs);
	}

	SIMD256 SIMDFunctions::divVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_div_ps(lhs, rhs);
	}

	SIMD256 SIMDFunctions::andVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_and_ps(lhs, rhs);
	}

	SIMD256 SIMDFunctions::orVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_or_ps(lhs, rhs);
	}

	SIMD256 SIMDFunctions::xorVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_xor_ps(lhs, rhs);
	}

	SIMD256 SIMDFunctions::notVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_andnot_ps(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isEqualVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpeq_epu32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isNotEqualVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpneq_epu32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isLessThanVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmplt_epu32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isLessThanOrEqualVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmple_epu32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isGraterThanVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpgt_epu32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isGraterThanOrEqualVector256F(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpge_epu32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::addVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_add_pd(lhs, rhs);
	}

	SIMD256 SIMDFunctions::subVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_sub_pd(lhs, rhs);
	}

	SIMD256 SIMDFunctions::mulVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_mul_pd(lhs, rhs);
	}

	SIMD256 SIMDFunctions::divVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_div_pd(lhs, rhs);
	}

	SIMD256 SIMDFunctions::andVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_and_pd(lhs, rhs);
	}

	SIMD256 SIMDFunctions::orVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_or_pd(lhs, rhs);
	}

	SIMD256 SIMDFunctions::xorVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_xor_pd(lhs, rhs);
	}

	SIMD256 SIMDFunctions::notVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_andnot_pd(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isEqualVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpeq_epu64_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isNotEqualVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpneq_epu64_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isLessThanVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmplt_epu64_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isLessThanOrEqualVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmple_epu64_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isGraterThanVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpgt_epu64_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isGraterThanOrEqualVector256D(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpge_epu64_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::addVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_add_epi32(lhs, rhs);
	}

	SIMD256 SIMDFunctions::subVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_sub_epi32(lhs, rhs);
	}

	SIMD256 SIMDFunctions::mulVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_mul_epi32(lhs, rhs);
	}

	SIMD256 SIMDFunctions::divVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_div_epi32(lhs, rhs);
	}

	SIMD256 SIMDFunctions::andVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_and_si256(lhs, rhs);
	}

	SIMD256 SIMDFunctions::orVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_or_si256(lhs, rhs);
	}

	SIMD256 SIMDFunctions::xorVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_xor_si256(lhs, rhs);
	}

	SIMD256 SIMDFunctions::notVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_andnot_si256(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isEqualVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpeq_epi32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isNotEqualVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpneq_epi32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isLessThanVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmplt_epi32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isLessThanOrEqualVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmple_epi32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isGraterThanVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpgt_epi32_mask(lhs, rhs);
	}

	SIMD256 SIMDFunctions::isGraterThanOrEqualVector256I(SIMD256 lhs, SIMD256 rhs)
	{
		return _mm256_cmpge_epi32_mask(lhs, rhs);
	}

	/* ---------- 512 bit operations ---------- */
	SIMD512 SIMDFunctions::addVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_add_ps(lhs, rhs);
	}

	SIMD512 SIMDFunctions::subVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_sub_ps(lhs, rhs);
	}

	SIMD512 SIMDFunctions::mulVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_mul_ps(lhs, rhs);
	}

	SIMD512 SIMDFunctions::divVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_div_ps(lhs, rhs);
	}

	SIMD512 SIMDFunctions::andVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_and_ps(lhs, rhs);
	}

	SIMD512 SIMDFunctions::orVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_or_ps(lhs, rhs);
	}

	SIMD512 SIMDFunctions::xorVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_xor_ps(lhs, rhs);
	}

	SIMD512 SIMDFunctions::notVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_andnot_ps(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isEqualVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpeq_epu32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isNotEqualVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpneq_epu32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isLessThanVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmplt_epu32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isLessThanOrEqualVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmple_epu32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isGraterThanVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpgt_epu32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isGraterThanOrEqualVector512F(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpge_epu32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::addVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_add_pd(lhs, rhs);
	}

	SIMD512 SIMDFunctions::subVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_sub_pd(lhs, rhs);
	}

	SIMD512 SIMDFunctions::mulVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_mul_pd(lhs, rhs);
	}

	SIMD512 SIMDFunctions::divVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_div_pd(lhs, rhs);
	}

	SIMD512 SIMDFunctions::andVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_and_pd(lhs, rhs);
	}

	SIMD512 SIMDFunctions::orVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_or_pd(lhs, rhs);
	}

	SIMD512 SIMDFunctions::xorVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_xor_pd(lhs, rhs);
	}

	SIMD512 SIMDFunctions::notVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_andnot_pd(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isEqualVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpeq_epu64_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isNotEqualVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpneq_epu64_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isLessThanVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmplt_epu64_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isLessThanOrEqualVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmple_epu64_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isGraterThanVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpgt_epu64_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isGraterThanOrEqualVector512D(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpge_epu64_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::addVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_add_epi32(lhs, rhs);
	}

	SIMD512 SIMDFunctions::subVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_sub_epi32(lhs, rhs);
	}

	SIMD512 SIMDFunctions::mulVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_mul_epi32(lhs, rhs);
	}

	SIMD512 SIMDFunctions::divVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_div_epi32(lhs, rhs);
	}

	SIMD512 SIMDFunctions::andVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_and_si512(lhs, rhs);
	}

	SIMD512 SIMDFunctions::orVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_or_si512(lhs, rhs);
	}

	SIMD512 SIMDFunctions::xorVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_xor_si512(lhs, rhs);
	}

	SIMD512 SIMDFunctions::notVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_andnot_si512(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isEqualVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpeq_epi32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isNotEqualVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpneq_epi32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isLessThanVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmplt_epi32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isLessThanOrEqualVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmple_epi32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isGraterThanVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpgt_epi32_mask(lhs, rhs);
	}

	SIMD512 SIMDFunctions::isGraterThanOrEqualVector512I(SIMD512 lhs, SIMD512 rhs)
	{
		return _mm512_cmpge_epi32_mask(lhs, rhs);
	}
}