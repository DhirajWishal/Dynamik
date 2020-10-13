// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_MATRIX_3_F
#define _DYNAMIK_MATH_MATRIX_3_F

#include "Matrix.h"
#include "../Vector/Vector3F.h"

class DMK_API Matrix3F;

/* Vector 3D type traits */
template <>
struct DMK_API MatrixTraits<Matrix3F>
{
	typedef float type;
};

class DMK_API Matrix3F : public Matrix<Matrix3F>
{
public:
	Matrix3F();
	Matrix3F(float value);
	Matrix3F(Vector3F vec1, Vector3F vec2, Vector3F vec3);
	Matrix3F(
		float a, float b, float c,
		float d, float e, float f,
		float g, float h, float i);
	Matrix3F(const Matrix3F& other);
	Matrix3F(std::initializer_list<float> list);
	~Matrix3F() {}

	Matrix3F operator=(const Matrix3F& other);
	Vector3F& operator[](UI32 index) const;

public:
	union
	{
		struct { Vector3F x, y, z; };
		struct { Vector3F r, g, b; };
	};
};

#endif // !_DYNAMIK_MATRIX_3_F
