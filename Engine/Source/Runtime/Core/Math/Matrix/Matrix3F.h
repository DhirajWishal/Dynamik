#pragma once
#ifndef _DYNAMIK_MATH_MATRIX_3_F
#define _DYNAMIK_MATH_MATRIX_3_F

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/
#include "Matrix.h"
#include "../Vector/Vector3F.h"

namespace Dynamik
{
	class DMK_API Matrix3F;

	/* Vector 3D type traits */
	template <>
	struct DMK_API MatrixTraits<Matrix3F>
	{
		typedef F32 type;
	};

	class DMK_API Matrix3F : public Matrix<Matrix3F>
	{
	public:
		Matrix3F();
		Matrix3F(F32 value);
		Matrix3F(Vector3F vec1, Vector3F vec2, Vector3F vec3);
		Matrix3F(
			F32 a, F32 b, F32 c,
			F32 d, F32 e, F32 f,
			F32 g, F32 h, F32 i);
		Matrix3F(const Matrix3F& other);
		Matrix3F(std::initializer_list<F32> list);
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
}

#endif // !_DYNAMIK_MATRIX_3_F
