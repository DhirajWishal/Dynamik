// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_VECTOR_2F_H
#define _DYNAMIK_MATH_VECTOR_2F_H

#include "Vector.h"

class DMK_API Vector2F;

/* Vector 2F type traits */
template <>
struct DMK_API VectorTraits<Vector2F>
{
	typedef float type;
};

/*
 2D float Vector class for the Dynamik Engine
*/
class Vector2F : public Vector<Vector2F>
{
public:
	Vector2F() : x(0.0f), y(0.0f) {}
	Vector2F(float value) : x(value), y(value) {}
	Vector2F(float value1, float value2) : x(value1), y(value2) {}
	Vector2F(std::initializer_list<float> list);
	~Vector2F() {}

	Vector2F operator=(const std::initializer_list<float>& list);
	float& operator[](UI32 index) const;

public:
	union
	{
		struct { float x, y; };
		struct { float a, b; };
		struct { float width, height; };
	};
};

Vector2F operator+(const Vector2F& lhs, const Vector2F& rhs);
Vector2F operator-(const Vector2F& lhs, const Vector2F& rhs);
Vector2F operator*(const Vector2F& lhs, const Vector2F& rhs);
Vector2F operator/(const Vector2F& lhs, const Vector2F& rhs);

Vector2F operator+(const Vector2F& lhs, const float& value);
Vector2F operator-(const Vector2F& lhs, const float& value);
Vector2F operator*(const Vector2F& lhs, const float& value);
Vector2F operator/(const Vector2F& lhs, const float& value);

bool operator==(const Vector2F& lhs, const Vector2F& rhs);
bool operator!=(const Vector2F& lhs, const Vector2F& rhs);
bool operator<(const Vector2F& lhs, const Vector2F& rhs);
bool operator<=(const Vector2F& lhs, const Vector2F& rhs);
bool operator>(const Vector2F& lhs, const Vector2F& rhs);
bool operator>=(const Vector2F& lhs, const Vector2F& rhs);

bool operator&&(const Vector2F& lhs, const Vector2F& rhs);
bool operator||(const Vector2F& lhs, const Vector2F& rhs);
bool operator^(const Vector2F& lhs, const Vector2F& rhs);
bool operator~(const Vector2F& rhs);
bool operator!(const Vector2F& rhs);

#endif // !_DYNAMIK_VECTOR_2F_H
