// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_VECTOR_4F_H
#define _DYNAMIK_MATH_VECTOR_4F_H

/*
 4D Vector for the Dynamik Engine.
*/
#include "Vector.h"

class DMK_API Vector4F;

/* Vector 4D type traits */
template <>
struct DMK_API VectorTraits<Vector4F>
{
	typedef float type;
};

/*
 Basic 4D Vector for the Dynamik Engine.
 This class uses SIMD to carry out the necessary calculations.
*/
class DMK_API Vector4F : public Vector<Vector4F> {
public:
	Vector4F() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
	Vector4F(float value) : r(value), g(value), b(value), a(value) {}
	Vector4F(float value1, float value2, float value3, float value4) : r(value1), g(value2), b(value3), a(value4) {}
	Vector4F(const Vector4F& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}
	Vector4F(std::initializer_list<float> list);
	Vector4F(const float* ptr);
	~Vector4F() {}

	Vector4F operator=(const std::initializer_list<float>& list);
	float& operator[](UI32 index) const;

	operator float* () const;

	union
	{
		struct { float r, g, b, a; };
		struct { float x, y, z, w; };
		struct { float width, height, depth, zero; };
	};
};

Vector4F operator+(const Vector4F& lhs, const Vector4F& rhs);
Vector4F operator-(const Vector4F& lhs, const Vector4F& rhs);
Vector4F operator*(const Vector4F& lhs, const Vector4F& rhs);
Vector4F operator/(const Vector4F& lhs, const Vector4F& rhs);

Vector4F operator+(const Vector4F& lhs, const float& value);
Vector4F operator-(const Vector4F& lhs, const float& value);
Vector4F operator*(const Vector4F& lhs, const float& value);
Vector4F operator/(const Vector4F& lhs, const float& value);

bool operator==(const Vector4F& lhs, const Vector4F& rhs);
bool operator!=(const Vector4F& lhs, const Vector4F& rhs);
bool operator<(const Vector4F& lhs, const Vector4F& rhs);
bool operator<=(const Vector4F& lhs, const Vector4F& rhs);
bool operator>(const Vector4F& lhs, const Vector4F& rhs);
bool operator>=(const Vector4F& lhs, const Vector4F& rhs);

bool operator&&(const Vector4F& lhs, const Vector4F& rhs);
bool operator||(const Vector4F& lhs, const Vector4F& rhs);
bool operator^(const Vector4F& lhs, const Vector4F& rhs);
bool operator~(const Vector4F& rhs);
bool operator!(const Vector4F& rhs);

#endif // !_DYNAMIK_MATH_VECTOR_4F_H
