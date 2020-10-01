// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_MATRIX_4F_H
#define _DYNAMIK_MATH_MATRIX_4F_H

/*
 4D Matrix for the Dynamik Engine.
*/
#include "Matrix.h"
#include "../Vector/Vector4F.h"

class DMK_API Matrix4F;

/* Vector 4D type traits */
template <>
struct DMK_API MatrixTraits<Matrix4F>
{
	typedef float type;
};

/*
 4x4 Matrix for the Dynamik Engine.
*/
class DMK_API Matrix4F : public Matrix<Matrix4F>
{
public:
	Matrix4F();
	Matrix4F(float value);
	Matrix4F(Vector4F vec1, Vector4F vec2, Vector4F vec3, Vector4F vec4);
	Matrix4F(
		float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p);
	Matrix4F(const Matrix4F& other);
	Matrix4F(std::initializer_list<float> list);
	~Matrix4F() {}

	Matrix4F operator=(const Matrix4F& other);
	Vector4F& operator[](UI32 index) const;

public:
	union
	{
		struct { Vector4F r, g, b, a; };
		struct { Vector4F x, y, z, w; };
	};

public:		/* Utilities */
	static Matrix4F Identity;
};

Matrix4F operator*(const Matrix4F& lhs, const float& rhs);

#endif // !_DYNAMIK_MATH_MATRIX_4F_H
