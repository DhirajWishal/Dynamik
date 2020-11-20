// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Matrix.h"
#include "Core/Maths/Vector/Vector2.h"

namespace DMK
{
	class Matrix22;

	/**
	 * Matrix 2x2 type traits.
	 */
	template <>
	struct MatrixTraits<Matrix22>
	{
		typedef float type;
	};

	/**
	 * Matrix 2x2 for the Engine Dev Kit.
	 */
	class Matrix22 : public Matrix<Matrix22>
	{
	public:
		/**
		 * Default constructor.
		 */
		Matrix22();

		/**
		 * Construct the matrix using one value.
		 *
		 * @param value: The value to be constructed with.
		 */
		Matrix22(float value);

		/**
		 * Set values to the matrix using two 2D vectors.
		 *
		 * @param vec1: Vector one.
		 * @param vec2: Vector two.
		 */
		Matrix22(Vector2 vec1, Vector2 vec2);

		/**
		 * Construct the matrix by setting individual values.
		 *
		 * @param a: Value to be set to x.
		 * @param b: Value to be set to y.
		 * @param c: Value to be set to z.
		 * @param d: Value to be set to w.
		 */
		Matrix22(
			float a, float b,
			float c, float d);

		/**
		 * Construct the matrix using another matrix of the same type.
		 *
		 * @param other: The other matrix.
		 */
		Matrix22(const Matrix22& other);

		/**
		 * Construct the matrix using an initializer list.
		 *
		 * @param list: The initializer list.
		 */
		Matrix22(std::initializer_list<float> list);

		/**
		 * Default destructor.
		 */
		~Matrix22() {}

		/**
		 * Assign data from another matrix of the same type.
		 *
		 * @param other: The other matrix.
		 * @return The value updated matrix.
		 */
		Matrix22 operator=(const Matrix22& other);

		/**
		 * Get a row of the matrix using the index.
		 *
		 * @param index: The index of the row.
		 * @return The requested row.
		 */
		const Vector2 operator[](UI32 index) const;

		/**
		 * Get a row of the matrix using the index.
		 *
		 * @param index: The index of the row.
		 * @return The requested row.
		 */
		Vector2& operator[](UI32 index);

		/**
		 * Multiply the matrix by a value.
		 *
		 * @param value: The value to be multiplied with.
		 * @return The multiplied matrix.
		 */
		Matrix22& operator*(const float& value);

		/**
		 * Multiplication operator.
		 * Matrix * Vector.
		 *
		 * @param other: The vector 2D.
		 * @return The multiplied vector 2D.
		 */
		Vector2 operator*(const Vector2& other);

		/**
		 * Multiplication operator.
		 *
		 * @param other: The other matrix to be multiplied with.
		 * @return The multiplied matrix.
		 */
		Matrix22& operator*(const Matrix22& other);

	public:
		union
		{
			struct { Vector2 x, y; };
			struct { Vector2 r, g; };
		};
	};
}
