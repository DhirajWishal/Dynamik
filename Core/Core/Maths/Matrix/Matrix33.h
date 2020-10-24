// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_MATHS_MATRIX_33_H
#define _DYNAMIK_CORE_MATHS_MATRIX_33_H

#include "Matrix.h"
#include "Core/Maths/Vector/Vector3.h"

namespace DMK
{
	class Matrix33;

	/**
	 * Matrix 3x3 type traits.
	 */
	template <>
	struct MatrixTraits<Matrix33>
	{
		typedef float type;
	};

	/**
	 * Matrix 3x3 for the Engine Dev Kit.
	 */
	class Matrix33 : public Matrix<Matrix33>
	{
	public:
		/**
		 * Default constructor.
		 */
		Matrix33();

		/**
		 * Construct the matrix using one value.
		 *
		 * @param value: The value to be constructed with.
		 */
		Matrix33(float value);

		/**
		 * Construct the matrix using 3 Vector 3D structures.
		 *
		 * @param vec1: Vector one.
		 * @param vec2: Vector two.
		 * @param vec3: Vector three.
		 */
		Matrix33(Vector3 vec1, Vector3 vec2, Vector3 vec3);

		/**
		 * Construct the matrix using individual values.
		 *
		 * @param a: Value to be set to x.x.
		 * @param b: Value to be set to x.y.
		 * @param c: Value to be set to x.z.
		 * @param d: Value to be set to y.x.
		 * @param e: Value to be set to y.y.
		 * @param f: Value to be set to y.z.
		 * @param g: Value to be set to z.x.
		 * @param h: Value to be set to z.y.
		 * @param i: Value to be set to z.z.
		 */
		Matrix33(
			float a, float b, float c,
			float d, float e, float f,
			float g, float h, float i);

		/**
		 * Construct the matrix using another matrix of the same type.
		 *
		 * @param other: The other matrix.
		 */
		Matrix33(const Matrix33& other);

		/**
		 * Construct the matrix using an initializer list.
		 *
		 * @param list: The initializer list.
		 */
		Matrix33(std::initializer_list<float> list);

		/**
		 * Default constructor.
		 */
		~Matrix33() {}

		/**
		 * Assign data from another matrix of the same type.
		 *
		 * @param other: The other matrix.
		 * @return: The value updated matrix.
		 */
		Matrix33 operator=(const Matrix33& other);

		/**
		 * Retrieve a row by using the index.
		 *
		 * @param index: The index of the row.
		 * @return: The Vector 3D row.
		 */
		Vector3& operator[](UI32 index) const;

		/**
		 * Multiply the matrix by a value.
		 *
		 * @param value: The value to be multiplied with.
		 * @return: The multiplied matrix.
		 */
		Matrix33& operator*(const float& value);

		/**
		 * Multiplication operator.
		 * Matrix * Vector.
		 *
		 * @param other: The vector 3D.
		 * @return: The multiplied vector 3D.
		 */
		Vector3 operator*(const Vector3& other);

		/**
		 * Multiplication operator.
		 *
		 * @param other: The other matrix to be multiplied with.
		 * @return: The multiplied matrix.
		 */
		Matrix33& operator*(const Matrix33& other);

	public:
		union
		{
			struct { Vector3 x, y, z; };
			struct { Vector3 r, g, b; };
		};
	};
}

#endif // !_DYNAMIK_CORE_MATHS_MATRIX_33_H
