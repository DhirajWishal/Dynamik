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

#include "Matrix/Matrix4F.h"

namespace Dynamik
{
	/*
	 Dynamik Math Functions
	*/
	class DMKMathFunctions {
	public:
		/*
		 Absolute value of a integer
		*/
		I32 abs(I32 value);

	public:
		/*
		 Dot product of two vectors (3D)
		*/
		static F32 dot(Vector3F lhs, Vector3F rhs);

		/*
		 Dot product of two vectors (4D)
		*/
		static F32 dot(Vector4F lhs, Vector4F rhs);

		/*
		 Convert radians to degrees
		*/
		static F32 degrees(F32 const radians);

		/*
		 Convert degrees to radians
		*/
		static F32 radians(F32 const degrees);

	public:
		/*
		 Cross peoduct of two vectors (3D)
		*/
		static Vector3F cross(Vector3F lhs, Vector3F rhs);

		/*
		 Normalize a vector (3D)
		*/
		static Vector3F normalize(Vector3F rhs);

	public:
		/*
		 Look at matrix
		*/
		static Matrix4F lookAt(Vector3F const eye, Vector3F const center, Vector3F const up);

		/*
		 Perspective matrix
		*/
		static Matrix4F perspective(F32 FOV, F32 aspect, F32 near, F32 far, B1 flipYAxis = true);

		/*
		 Translate matrix
		*/
		static Matrix4F translate(Matrix4F mat, Vector3F const vec);

		/*
		 Rotate matrix
		*/
		static Matrix4F rotate(Matrix4F const mat, F32 const angel, Vector3F const vec);
	};
}

#endif // !_DYNAMIK_MATH_FUNCTIONS_H
