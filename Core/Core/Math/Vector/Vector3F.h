// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_VECTOR_3F_H
#define _DYNAMIK_MATH_VECTOR_3F_H

/*
 3D Vector for the Dynamik Engine.
*/
#include "Vector.h"

class DMK_API Vector3F;

/* Vector 3D type traits */
template <>
struct DMK_API VectorTraits<Vector3F>
{
	typedef float type;
};

/*
 Basic 3D Vector for the Dynamik Engine.
 This class uses SIMD to carry out the necessary calculations.
*/
class DMK_API Vector3F : public Vector<Vector3F> {
public:
	Vector3F() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector3F(float value) : x(value), y(value), z(value), w(value) {}
	Vector3F(float value1, float value2, float value3) : x(value1), y(value2), z(value3), w(0.0f) {}
	Vector3F(const Vector3F& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
	Vector3F(std::initializer_list<float> list);
	Vector3F(const float* ptr);
	~Vector3F() {}

	Vector3F operator=(const std::initializer_list<float>& other);
	float& operator[](UI32 index) const;

	operator float* () const;

	union
	{
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
		struct { float width, height, depth, zero; };
	};
};

Vector3F operator+(const Vector3F& lhs, const Vector3F& rhs);
Vector3F operator-(const Vector3F& lhs, const Vector3F& rhs);
Vector3F operator*(const Vector3F& lhs, const Vector3F& rhs);
Vector3F operator/(const Vector3F& lhs, const Vector3F& rhs);

Vector3F operator+(const Vector3F& lhs, const float& value);
Vector3F operator-(const Vector3F& lhs, const float& value);
Vector3F operator*(const Vector3F& lhs, const float& value);
Vector3F operator/(const Vector3F& lhs, const float& value);

bool operator==(const Vector3F& lhs, const Vector3F& rhs);
bool operator!=(const Vector3F& lhs, const Vector3F& rhs);
bool operator<(const Vector3F& lhs, const Vector3F& rhs);
bool operator<=(const Vector3F& lhs, const Vector3F& rhs);
bool operator>(const Vector3F& lhs, const Vector3F& rhs);
bool operator>=(const Vector3F& lhs, const Vector3F& rhs);

bool operator&&(const Vector3F& lhs, const Vector3F& rhs);
bool operator||(const Vector3F& lhs, const Vector3F& rhs);
bool operator^(const Vector3F& lhs, const Vector3F& rhs);
bool operator~(const Vector3F& rhs);
bool operator!(const Vector3F& rhs);

#endif // !_DYNAMIK_MATH_VECTOR_3F_H