// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_MATHS_MATRIX_44_H
#define _DYNAMIK_CORE_MATHS_MATRIX_44_H

#include "Matrix.h"
#include "Core/Maths/Vector/Vector4.h"

namespace DMK
{
	class Matrix44;

	/**
	 * Matrix 4x4 type traits.
	 */
	template <>
	struct MatrixTraits<Matrix44>
	{
		typedef float type;
	};

	/**
	 * Matrix 4x4 for the Engine Dev Kit.
	 */
	class Matrix44 : public Matrix<Matrix44>
	{
	public:
		/**
		 * Default constructor.
		 */
		Matrix44();

		/**
		 * Construct the matrix using a value.
		 *
		 * @param value: The value to cnstruct the matrix with.
		 */
		Matrix44(float value);

		/**
		 * Construct the matrix using 4 4D vectors.
		 *
		 * @param vec1: Vector one.
		 * @param vec2: Vector two.
		 * @param vec3: Vector three.
		 * @param vec4: Vector four.
		 */
		Matrix44(Vector4 vec1, Vector4 vec2, Vector4 vec3, Vector4 vec4);

		/**
		 * Construct the matrix using individual values.
		 *
		 * @param a: Value to be set to r.r.
		 * @param b: Value to be set to r.g.
		 * @param c: Value to be set to r.b.
		 * @param d: Value to be set to r.a.
		 * @param e: Value to be set to g.r.
		 * @param f: Value to be set to g.g.
		 * @param g: Value to be set to g.b.
		 * @param h: Value to be set to g.a.
		 * @param i: Value to be set to b.r.
		 * @param j: Value to be set to b.g.
		 * @param k: Value to be set to b.b.
		 * @param l: Value to be set to b.a.
		 * @param m: Value to be set to a.r.
		 * @param n: Value to be set to a.g.
		 * @param o: Value to be set to a.b.
		 * @param p: Value to be set to a.a.
		 */
		Matrix44(
			float a, float b, float c, float d,
			float e, float f, float g, float h,
			float i, float j, float k, float l,
			float m, float n, float o, float p);

		/**
		 * Construct the matrix using another matrix of the same type.
		 *
		 * @param other: The other matrix.
		 */
		Matrix44(const Matrix44& other);

		/**
		 * Construct the matrix using an initializer list.
		 *
		 * @param list: The initialize list.
		 */
		Matrix44(std::initializer_list<float> list);

		/**
		 * Default destructor.
		 */
		~Matrix44() {}

		/**
		 * Assign data from another matrix of the same type.
		 *
		 * @param other: The other matrix.
		 * @return: The value updated matrix.
		 */
		Matrix44 operator=(const Matrix44& other);

		/**
		 * Retrieve a row using the index.
		 *
		 * @param index: The index of the row.
		 * @return: Vector 4D row.
		 */
		Vector4& operator[](UI32 index) const;

		/**
		 * Multiply the matrix by a value.
		 *
		 * @param value: The value to be multiplied with.
		 * @return: The multiplied matrix.
		 */
		Matrix44& operator*(const float& value);

		/**
		 * Multiplication operator.
		 * Matrix * Vector.
		 *
		 * @param other: The vector 4D.
		 * @return: The multiplied vector 4D.
		 */
		Vector4 operator*(const Vector4& other);

		/**
		 * Multiplication operator.
		 *
		 * @param other: The other matrix to be multiplied with.
		 * @return: The multiplied matrix.
		 */
		Matrix44& operator*(const Matrix44& other);

	public:
		union
		{
			struct { Vector4 r, g, b, a; };
			struct { Vector4 x, y, z, w; };
		};
	};

	Matrix44 operator*(const Matrix44& lhs, const float& rhs);
}

#endif // !_DYNAMIK_CORE_MATHS_MATRIX_44_H
