#pragma once
#ifndef _DYNAMIK_MATH_FUNCTIONS_H
#define _DYNAMIK_MATH_FUNCTIONS_H

/*
 SIMD Math functions for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "../Object/Object.h"
#include "Vector3D.h"
#include "Vector4D.h"

namespace Dynamik
{
	class DMKMathFunctions : public DMKObject {
		DMK_CLASS_FUNCTIONAL(DMKMathFunctions)
	public:
		static Vector3D dotProduct(Vector3D lhs, Vector3D rhs);
	};
}

#endif // !_DYNAMIK_MATH_FUNCTIONS_H
