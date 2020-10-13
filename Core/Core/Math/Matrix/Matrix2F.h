// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_MATRIX_2F_H
#define _DYNAMIK_MATH_MATRIX_2F_H

#include "Matrix.h"
#include "../Vector/Vector2F.h"

class DMK_API Matrix2F;

/* Matrix 2D type traits */
template <>
struct DMK_API MatrixTraits<Matrix2F>
{
	typedef float type;
};

class DMK_API Matrix2F : public Matrix<Matrix2F>
{
public:
	Matrix2F();
	Matrix2F(float value);
	Matrix2F(Vector2F vec1, Vector2F vec2);
	Matrix2F(
		float a, float b,
		float c, float d);
	Matrix2F(const Matrix2F& other);
	Matrix2F(std::initializer_list<float> list);
	~Matrix2F() {}

	Matrix2F operator=(const Matrix2F& other);
	Vector2F& operator[](UI32 index) const;

public:
	union
	{
		struct { Vector2F x, y; };
		struct { Vector2F r, g; };
	};
};

#endif // !_DYNAMIK_MATH_MATRIX_2F_H
