// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_FUNCTIONS_H
#define _DYNAMIK_MATH_FUNCTIONS_H

/*
 SIMD Math functions for the Dynamik Engine.
*/

#include "Vector/Vector3F.h"
#include "Vector/Vector4F.h"

#include "Matrix/Matrix4F.h"

#include "Quaternion.h"

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
		static I32 abs(I32 value);

		/*
		 Check if the given value is not a number.
		*/
		static B1 isNaN(F32 value);

		/*
		 Check if the given value is not a number.
		*/
		static B1 isNaN(I32 value);

		/*
		 Check if the value is in the finite range.
		*/
		static B1 isFinite(F32 value);

		/*
		 Check if the value is in the finite range.
		*/
		static B1 isFinite(I32 value);

		/*
		 Check if the value is infinite.
		*/
		static B1 isInfinite(F32 value);

		/*
		 Check if the value is infinite.
		*/
		static B1 isInfinite(I32 value);

		/*
		 Add all values together.
		*/
		static DMK_FORCEINLINE F32 addAll(Vector4F const vector);

		/*
		 Get the sin value of a given value.

		 @param radians: The value in radians.
		*/
		static F32 sin(F32 radians);

		/*
		 Get the cos value of a given value.

		 @param radians: The value in radians.
		*/
		static F32 cos(F32 radians);

		/*
		 Get the tan value of a given value.

		 @param radians: The value in radians.
		*/
		static F32 tan(F32 radians);

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
		 Cross product of two vectors (3D)
		*/
		static Vector3F cross(Vector3F lhs, Vector3F rhs);

		/*
		 Normalize a vector (3D)
		*/
		static Vector3F normalize(Vector3F rhs);

		/*
		 Normalize a vector (4D)
		*/
		static Vector4F normalize(Vector4F rhs);

	public:
		/*
		 Multiply two Matrix4Fs
		*/
		static Matrix4F multiply(Matrix4F const& lhs, Matrix4F const& rhs);

		/*
		 Multiply a matrix and a vector.
		*/
		static Vector4F multiply(Matrix4F const& lhs, Vector4F const& rhs);

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
		 Scale matrix
		*/
		static Matrix4F scale(Matrix4F mat, Vector3F const vec);

		/*
		 Rotate matrix
		*/
		static Matrix4F rotate(Matrix4F const mat, F32 const angel, Vector3F const vec);

		/*
		 Inverse matrix
		*/
		static Matrix4F inverse(Matrix4F const& mat);

	public:		/* Quaternion Functions */
		/*
		 Interpolate quaternion.
		*/
		static Quaternion interpolate(Quaternion const& start, Quaternion const& end, const F32& blend);

		/*
		 Interpolate Vector 3D.
		*/
		static Vector3F interpolate(Vector3F const& start, Vector3F const& end, const F32& progression);

		/*
		 Convert the quaternion to a rotational matrix.
		*/
		static Matrix4F toRotationalMatrix(Quaternion const& quat);
	};

	/* Short form type for the math class */
	typedef DMKMathFunctions DMathLib;

	/* ---------- GLOBAL OPERATORS ---------- */
	/*
	 Multiply two 4x4 matrices.

	 @param lhs: Left matrix.
	 @param rhs: Right matrix.
	*/
	DMK_FORCEINLINE Matrix4F operator*(const Matrix4F& lhs, const Matrix4F& rhs)
	{
		return DMKMathFunctions::multiply(lhs, rhs);
	}

	/*
	 Multiply a Matrix4F with a Vector4F.

	 @param lhs: The matrix.
	 @param rhs: The vector.
	*/
	DMK_FORCEINLINE Vector4F operator*(const Matrix4F& lhs, const Vector4F& rhs)
	{
		return DMKMathFunctions::multiply(lhs, rhs);
	}
}

#endif // !_DYNAMIK_MATH_FUNCTIONS_H