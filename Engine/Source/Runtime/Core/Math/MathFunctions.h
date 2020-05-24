#pragma once
#ifndef _DYNAMIK_MATH_FUNCTIONS_H
#define _DYNAMIK_MATH_FUNCTIONS_H

/*
 SIMD Math functions for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "Vector/Vector3F.h"
#include "Vector/Vector3D.h"
#include "Vector/Vector4F.h"
#include "Vector/Vector4D.h"

namespace Dynamik
{
	class DMKMathFunctions {
	public:
		static Vector3F dotProduct(Vector3F lhs, Vector3F rhs);
	};
}

#endif // !_DYNAMIK_MATH_FUNCTIONS_H
