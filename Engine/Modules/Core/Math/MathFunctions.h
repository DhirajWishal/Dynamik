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
	static bool isNaN(float value);

	/*
	 Check if the given value is not a number.
	*/
	static bool isNaN(I32 value);

	/*
	 Check if the value is in the finite range.
	*/
	static bool isFinite(float value);

	/*
	 Check if the value is in the finite range.
	*/
	static bool isFinite(I32 value);

	/*
	 Check if the value is infinite.
	*/
	static bool isInfinite(float value);

	/*
	 Check if the value is infinite.
	*/
	static bool isInfinite(I32 value);

	/*
	 Add all values together.
	*/
	static DMK_FORCEINLINE float addAll(Vector4F const vector);

	/*
	 Get the sin value of a given value.

	 @param radians: The value in radians.
	*/
	static float sin(float radians);

	/*
	 Get the cos value of a given value.

	 @param radians: The value in radians.
	*/
	static float cos(float radians);

	/*
	 Get the tan value of a given value.

	 @param radians: The value in radians.
	*/
	static float tan(float radians);

public:
	/*
	 Dot product of two vectors (3D)
	*/
	static float dot(Vector3F lhs, Vector3F rhs);

	/*
	 Dot product of two vectors (4D)
	*/
	static float dot(Vector4F lhs, Vector4F rhs);

	/*
	 Convert radians to degrees
	*/
	static float degrees(float const radians);

	/*
	 Convert degrees to radians
	*/
	static float radians(float const degrees);

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
	static Matrix4F perspective(float FOV, float aspect, float near, float far, bool flipYAxis = true);

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
	static Matrix4F rotate(Matrix4F const mat, float const angel, Vector3F const vec);

	/*
	 Inverse matrix
	*/
	static Matrix4F inverse(Matrix4F const& mat);

public:		/* Quaternion Functions */
	/*
	 Interpolate quaternion.
	*/
	static Quaternion interpolate(Quaternion const& start, Quaternion const& end, const float& blend);

	/*
	 Interpolate Vector 3D.
	*/
	static Vector3F interpolate(Vector3F const& start, Vector3F const& end, const float& progression);

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

#endif // !_DYNAMIK_MATH_FUNCTIONS_H