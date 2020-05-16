#pragma once
#ifndef _DYNAMIK_SIMD_FUNCTIONS_H
#define _DYNAMIK_SIMD_FUNCTIONS_H

/*
 Author:    Dhiraj Wishal
 Date:      16/05/2020
*/
#include "Object/Object.h"
#include "SIMD128.h"
#include "SIMD512.h"

namespace Dynamik
{
	DMK_ALIGN class DMK_API SIMDFunctions {
		DMK_CLASS_FUNCTIONAL(SIMDFunctions)
	public:
		/* Arithmetic operations */
		static SIMD128 addVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 subVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 mulVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 divVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 andVector128(SIMD128 lhs, SIMD128 rhs);

		/* Logical operations */
		static SIMD128 orVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 xorVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 notVector128(SIMD128 lhs, SIMD128 rhs);

		/* Comparison operators */
		static SIMD128 isEqualVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isNotEqualVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isLessThanVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isLessThanOrEqualVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isGraterThanVector128(SIMD128 lhs, SIMD128 rhs);
		static SIMD128 isGraterThanOrEqualVector128(SIMD128 lhs, SIMD128 rhs);

#if 0
		/* Arithmetic operations */
		static SIMD64 addVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 subVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 mulVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 divVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 andVector2F(SIMD64 lhs, SIMD64 rhs);

		/* Logical operations */
		static SIMD64 orVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 xorVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 notVector2F(SIMD64 lhs, SIMD64 rhs);

		/* Comparison operators */
		static SIMD64 isEqualVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 isNotEqualVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 isLessThanVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 isLessOrEqualVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 isGraterThanVector2F(SIMD64 lhs, SIMD64 rhs);
		static SIMD64 isGraterThanOrEqualVector2F(SIMD64 lhs, SIMD64 rhs);
#endif
	};
}

#endif // !_DYNAMIK_SIMD_FUNCTIONS_H
