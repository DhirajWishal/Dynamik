// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_MATRIX_4F_H
#define _DYNAMIK_MATH_MATRIX_4F_H

/*
 4D Matrix for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      17/05/2020
*/
#include "Matrix.h"
#include "../Vector/Vector4F.h"

namespace Dynamik
{
	class DMK_API Matrix4F;

	/* Vector 4D type traits */
	template <>
	struct DMK_API MatrixTraits<Matrix4F>
	{
		typedef F32 type;
	};

	/*
	 4x4 Matrix for the Dynamik Engine.
	*/
	class DMK_API Matrix4F : public Matrix<Matrix4F>
	{
	public:
		Matrix4F();
		Matrix4F(F32 value);
		Matrix4F(Vector4F vec1, Vector4F vec2, Vector4F vec3, Vector4F vec4);
		Matrix4F(
			F32 a, F32 b, F32 c, F32 d,
			F32 e, F32 f, F32 g, F32 h,
			F32 i, F32 j, F32 k, F32 l,
			F32 m, F32 n, F32 o, F32 p);
		Matrix4F(const Matrix4F& other);
		Matrix4F(std::initializer_list<F32> list);
		~Matrix4F() {}

		Matrix4F operator=(const Matrix4F& other);
		Vector4F& operator[](UI32 index) const;

	public:
		union
		{
			struct { Vector4F r, g, b, a; };
			struct { Vector4F x, y, z, w; };
		};
	};
}

#endif // !_DYNAMIK_MATH_MATRIX_4F_H
