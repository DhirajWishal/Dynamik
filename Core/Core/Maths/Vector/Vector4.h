// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_MATHS_VECTOR_4_H
#define _DYNAMIK_CORE_MATHS_VECTOR_4_H

#include "Vector.h"
#include "Core/Types/DataTypes.h"
#include <initializer_list>

namespace DMK
{
	class Vector4;

	/**
	 * Vector 4D type traits.
	 */
	template <>
	struct VectorTraits<Vector4>
	{
		typedef float type;
	};

	/**
	 * Basic 4D Vector for the Engine Dev Kit.
	 * This class uses SIMD to carry out the necessary calculations.
	 */
	class Vector4 : public Vector<Vector4> {
	public:
		/**
		 * Default constructor.
		 */
		Vector4() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}

		/**
		 * Set data to all the variables using one value.
		 *
		 * @param value: The value to be set.
		 */
		Vector4(float value) : r(value), g(value), b(value), a(value) {}

		/**
		 * Set values to all the variables.
		 *
		 * @param value1: Value to be set to r/ x/ width.
		 * @param value2: Value to be set to g/ y/ height.
		 * @param value3: Value to be set to b/ z/ depth.
		 * @param value4: Value to be set to a/ w/ zero.
		 */
		Vector4(float value1, float value2, float value3, float value4) : r(value1), g(value2), b(value3), a(value4) {}

		/**
		 * Construct the vector using another vector of the same type.
		 *
		 * @param other: The other vector.
		 */
		Vector4(const Vector4& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}

		/**
		 * Construct the vector using an initializer list.
		 * The size of the list must be equal to 4.
		 *
		 * @param list: The initialize list.
		 */
		Vector4(std::initializer_list<float> list);

		/**
		 * Construct the vector using a float pointer.
		 *
		 * @param ptr: The float pointer.
		 */
		Vector4(const float* ptr);

		/**
		 * Default destructor.
		 */
		~Vector4() {}

		/**
		 * Load data from an initializer list.
		 *
		 * @param list: The initializer list.
		 * @return The data added vector (this).
		 */
		Vector4 operator=(const std::initializer_list<float>& list);

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

		union
		{
			struct { float r, g, b, a; };
			struct { float x, y, z, w; };
			struct { float width, height, depth, zero; };
		};
	};

	typedef Vector4 VEC4;

	/**
	 * Addition operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector4 operator+(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Subtraction operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Multiplication operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector4 operator*(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Division operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector4 operator/(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Addition operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector4 operator+(const Vector4& lhs, const float& value);

	/**
	 * Subtraction operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector4 operator-(const Vector4& lhs, const float& value);

	/**
	 * Multiplication operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector4 operator*(const Vector4& lhs, const float& value);

	/**
	 * Division operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector4 operator/(const Vector4& lhs, const float& value);

	/**
	 * Is equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator==(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Is not equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator!=(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Is less than operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator<(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Is less than or equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator<=(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Is grater than operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator>(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Is grater than or equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator>=(const Vector4& lhs, const Vector4& rhs);

	/**
	 * AND operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator&&(const Vector4& lhs, const Vector4& rhs);

	/**
	 * OR operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator||(const Vector4& lhs, const Vector4& rhs);

	/**
	 * XOR operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator^(const Vector4& lhs, const Vector4& rhs);

	/**
	 * Inverse NOT operator.
	 *
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator~(const Vector4& rhs);

	/**
	 * NOR operator.
	 *
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator!(const Vector4& rhs);
}

#endif // !_DYNAMIK_CORE_MATHS_VECTOR_4_H
