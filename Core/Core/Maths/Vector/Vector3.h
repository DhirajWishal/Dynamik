// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_MATHS_VECTOR_3_H
#define _DYNAMIK_CORE_MATHS_VECTOR_3_H

#include "Vector.h"
#include "Core/Types/DataTypes.h"
#include <initializer_list>

namespace DMK
{
	class Vector3;

	/**
	 * Vector type trait.
	 */
	template <>
	struct VectorTraits<Vector3>
	{
		typedef float type;
	};

	/**
	 * Basic 3D Vector for the Engine Dev Kit.
	 * This class uses SIMD to carry out the necessary calculations.
	 */
	class Vector3 : public Vector<Vector3> {
	public:
		/**
		 * Default constructor.
		 */
		Vector3() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

		/**
		 * Set one value to all the data stored.
		 *
		 * @param value: Value to be stored.
		 */
		Vector3(float value) : x(value), y(value), z(value), w(value) {}

		/**
		 * Values to be set to the internal variables.
		 *
		 * @param value1: Value to be set to x/ r/ width.
		 * @param value2: Value to be set to y/ g/ height.
		 * @param value3: Value to be set to z/ b/ depth.
		 */
		Vector3(float value1, float value2, float value3) : x(value1), y(value2), z(value3), w(0.0f) {}

		/**
		 * Construct the vector using another vector of the same type.
		 *
		 * @param other: The other vector.
		 */
		Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

		/**
		 * Construct the vector using an initializer list.
		 * The size of the list should be equal to 3.
		 *
		 * @param list: The initializer list.
		 */
		Vector3(std::initializer_list<float> list);

		/**
		 * Construct the vector using a float pointer.
		 *
		 * @param ptr: The float pointer.
		 */
		Vector3(const float* ptr);

		/**
		 * Default destructor.
		 */
		~Vector3() {}

		/**
		 * Load data from an initializer list.
		 *
		 * @param list: The initializer list.
		 * @return The data added vector (this).
		 */
		Vector3 operator=(const std::initializer_list<float>& other);

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
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { float width, height, depth, zero; };
		};
	};

	typedef Vector3 VEC3;

	/**
	 * Addition operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector3 operator+(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Subtraction operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Multiplication operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector3 operator*(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Division operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The calculated vector.
	 */
	Vector3 operator/(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Addition operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector3 operator+(const Vector3& lhs, const float& value);

	/**
	 * Subtraction operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector3 operator-(const Vector3& lhs, const float& value);

	/**
	 * Multiplication operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector3 operator*(const Vector3& lhs, const float& value);

	/**
	 * Division operator.
	 *
	 * @param lhs: LHS argument.
	 * @param value: RHS value.
	 * @return The calculated vector.
	 */
	Vector3 operator/(const Vector3& lhs, const float& value);

	/**
	 * Is equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator==(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Is not equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator!=(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Is less than operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator<(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Is less than or equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator<=(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Is grater than operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator>(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Is grater than or equal operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator>=(const Vector3& lhs, const Vector3& rhs);

	/**
	 * AND operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator&&(const Vector3& lhs, const Vector3& rhs);

	/**
	 * OR operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator||(const Vector3& lhs, const Vector3& rhs);

	/**
	 * XOR operator.
	 *
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator^(const Vector3& lhs, const Vector3& rhs);

	/**
	 * Inverse NOT operator.
	 *
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator~(const Vector3& rhs);

	/**
	 * NOR operator.
	 *
	 * @param rhs: RHS argument.
	 * @return Boolean value.
	 */
	bool operator!(const Vector3& rhs);
}

#endif // !_DYNAMIK_CORE_MATHS_VECTOR_3_H
