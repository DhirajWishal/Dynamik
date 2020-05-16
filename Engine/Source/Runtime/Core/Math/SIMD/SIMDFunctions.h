#pragma once
#ifndef _DYNAMIK_SIMD_FUNCTIONS_H
#define _DYNAMIK_SIMD_FUNCTIONS_H

/*
 Author:    Dhiraj Wishal
 Date:      16/05/2020
*/
#include "Object/Object.h"
#include "SIMD128.h"
#include "SIMD256.h"
#include "SIMD512.h"

namespace Dynamik
{
	/*
	 This function contains all the available primitive operations for the available SIMD data types.
	*/
	class DMK_API SIMDFunctions {
		DMK_CLASS_FUNCTIONAL(SIMDFunctions)
	public:
		/* ---------- 128 bit operations ---------- */
		/* Arithmetic operations */
		static SIMD128 addVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 subVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 mulVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 divVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 andVector128F(SIMD128 lhs, SIMD128 rhs);

		/* Logical operations */
		static SIMD128 orVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 xorVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 notVector128F(SIMD128 lhs, SIMD128 rhs);

		/* Comparison operators */
		static SIMD128 isEqualVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isNotEqualVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isLessThanVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isLessThanOrEqualVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isGraterThanVector128F(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isGraterThanOrEqualVector128F(SIMD128 lhs, SIMD128 rhs);

		/* Arithmetic operations */
		static SIMD128 addVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 subVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 mulVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 divVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 andVector128D(SIMD128 lhs, SIMD128 rhs);

		/* Logical operations */
		static SIMD128 orVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 xorVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 notVector128D(SIMD128 lhs, SIMD128 rhs);

		/* Comparison operators */
		static SIMD128 isEqualVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isNotEqualVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isLessThanVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isLessThanOrEqualVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isGraterThanVector128D(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isGraterThanOrEqualVector128D(SIMD128 lhs, SIMD128 rhs);

		/* Arithmetic operations */
		static SIMD128 addVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 subVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 mulVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 divVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 andVector128I(SIMD128 lhs, SIMD128 rhs);

		/* Logical operations */
		static SIMD128 orVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 xorVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 notVector128I(SIMD128 lhs, SIMD128 rhs);

		/* Comparison operators */
		static SIMD128 isEqualVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isNotEqualVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isLessThanVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isLessThanOrEqualVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isGraterThanVector128I(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isGraterThanOrEqualVector128I(SIMD128 lhs, SIMD128 rhs);

		/* ---------- 256 bit operations ---------- */
		/* Arithmetic operations */
		static SIMD256 addVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 subVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 mulVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 divVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 andVector256F(SIMD256 lhs, SIMD256 rhs);

		/* Logical operations */
		static SIMD256 orVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 xorVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 notVector256F(SIMD256 lhs, SIMD256 rhs);

		/* Comparison operators */
		static SIMD256 isEqualVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isNotEqualVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isLessThanVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isLessThanOrEqualVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isGraterThanVector256F(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isGraterThanOrEqualVector256F(SIMD256 lhs, SIMD256 rhs);

		/* Arithmetic operations */
		static SIMD256 addVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 subVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 mulVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 divVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 andVector256D(SIMD256 lhs, SIMD256 rhs);

		/* Logical operations */
		static SIMD256 orVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 xorVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 notVector256D(SIMD256 lhs, SIMD256 rhs);

		/* Comparison operators */
		static SIMD256 isEqualVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isNotEqualVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isLessThanVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isLessThanOrEqualVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isGraterThanVector256D(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isGraterThanOrEqualVector256D(SIMD256 lhs, SIMD256 rhs);

		/* Arithmetic operations */
		static SIMD256 addVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 subVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 mulVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 divVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 andVector256I(SIMD256 lhs, SIMD256 rhs);

		/* Logical operations */
		static SIMD256 orVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 xorVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 notVector256I(SIMD256 lhs, SIMD256 rhs);

		/* Comparison operators */
		static SIMD256 isEqualVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isNotEqualVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isLessThanVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isLessThanOrEqualVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isGraterThanVector256I(SIMD256 lhs, SIMD256 rhs);
		static SIMD256 isGraterThanOrEqualVector256I(SIMD256 lhs, SIMD256 rhs);

		/* ---------- 512 bit operations ---------- */
		/* Arithmetic operations */
		static SIMD512 addVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 subVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 mulVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 divVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 andVector512F(SIMD512 lhs, SIMD512 rhs);

		/* Logical operations */
		static SIMD512 orVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 xorVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 notVector512F(SIMD512 lhs, SIMD512 rhs);

		/* Comparison operators */
		static SIMD512 isEqualVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isNotEqualVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isLessThanVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isLessThanOrEqualVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isGraterThanVector512F(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isGraterThanOrEqualVector512F(SIMD512 lhs, SIMD512 rhs);

		/* Arithmetic operations */
		static SIMD512 addVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 subVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 mulVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 divVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 andVector512D(SIMD512 lhs, SIMD512 rhs);

		/* Logical operations */
		static SIMD512 orVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 xorVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 notVector512D(SIMD512 lhs, SIMD512 rhs);

		/* Comparison operators */
		static SIMD512 isEqualVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isNotEqualVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isLessThanVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isLessThanOrEqualVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isGraterThanVector512D(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isGraterThanOrEqualVector512D(SIMD512 lhs, SIMD512 rhs);

		/* Arithmetic operations */
		static SIMD512 addVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 subVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 mulVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 divVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 andVector512I(SIMD512 lhs, SIMD512 rhs);

		/* Logical operations */
		static SIMD512 orVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 xorVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 notVector512I(SIMD512 lhs, SIMD512 rhs);

		/* Comparison operators */
		static SIMD512 isEqualVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isNotEqualVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isLessThanVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isLessThanOrEqualVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isGraterThanVector512I(SIMD512 lhs, SIMD512 rhs);
		static SIMD512 isGraterThanOrEqualVector512I(SIMD512 lhs, SIMD512 rhs);
	};
}

#endif // !_DYNAMIK_SIMD_FUNCTIONS_H
