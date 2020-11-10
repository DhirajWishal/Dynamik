// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_MATHS_VECTOR_2_H
#define _DYNAMIK_CORE_MATHS_VECTOR_2_H

#include "Vector.h"
#include "Core/Types/DataTypes.h"
#include <initializer_list>

namespace DMK
{
	class Vector2;

	/**
	 * Vector type trait.
	 */
	template <>
	struct VectorTraits<Vector2>
	{
		typedef float type;
	};

	/**
	 * The 2D vector of the Engine Dev Kit.
	 */
	class Vector2 : public Vector<Vector2>
	{
	public:
		/**
		 * Default constructor.
		 */
		Vector2() : x(0.0f), y(0.0f) {}

		/**
		 * Constructu using one value which will be set to all (x, y)/ (a, b)/ (width, height).
		 *
		 * @param value: The value to be set with.
		 */
		Vector2(float value) : x(value), y(value) {}

		/**
		 * Set values to the stored data.
		 *
		 * @param value1: Value to be set to x/ a/ width.
		 * @param value2: Value to be set to y/ b/ height.
		 */
		Vector2(float value1, float value2) : x(value1), y(value2) {}

		/**
		 * Set data to the vector using an initializer list.
		 * The list size should be equal to 2.
		 *
		 * @param list: The initializer list.
		 */
		Vector2(std::initializer_list<float> list);

		/**
		 * Default destructor.
		 */
		~Vector2() {}

		/**
		 * Load data from an initializer list.
		 *
		 * @param list: The initializer list.
		 * @return The data added vector (this).
		 */
		Vector2 operator=(const std::initializer_list<float>& list);

		/**
		 * Get data using the [] operator.
		 *
		 * @param index: The index of the data to be accessed.
		 * @return Float value at the index.
		 */
		const float operator[](UI32 index) const;

		/**
		 * Get data using the [] operator.
		 *
		 * @param index: The index of the data to be accessed.
		 * @return Float value at the index.
		 */
		float& operator[](UI32 index);

		/**
		 * Return the address of this since it can be accessed by the [] operator.
		 */
		operator const float* () const;

	public:
		union
		{
			struct { float x, y; };
			struct { float a, b; };
			struct { float width, height; };
		};
	};

	typedef Vector2 VEC2;

	/**
	 * Addition operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector2 operator+(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Subtraction operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Multiplication operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector2 operator*(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Division operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector2 operator/(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Addition operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector2 operator+(const Vector2& lhs, const float& value);

	/**
	 * Subtraction operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector2 operator-(const Vector2& lhs, const float& value);

	/**
	 * Multiplication operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector2 operator*(const Vector2& lhs, const float& value);

	/**
	 * Division operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector2 operator/(const Vector2& lhs, const float& value);

	/**
	 * Is equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator==(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Is not equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator!=(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Is less than operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator<(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Is less than or equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator<=(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Is grater than operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator>(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Is grater than or equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator>=(const Vector2& lhs, const Vector2& rhs);

	/**
	 * AND operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator&&(const Vector2& lhs, const Vector2& rhs);

	/**
	 * OR operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator||(const Vector2& lhs, const Vector2& rhs);

	/**
	 * XOR operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator^(const Vector2& lhs, const Vector2& rhs);

	/**
	 * Inverse NOT operator.
	 *
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator~(const Vector2& rhs);

	/**
	 * NOR operator.
	 *
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator!(const Vector2& rhs);
}

#endif // !_DYNAMIK_CORE_MATHS_VECTOR_2_H
