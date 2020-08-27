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
	typedef F32 type;
};

/*
 2D float Vector class for the Dynamik Engine
*/
class Vector2F : public Vector<Vector2F>
{
public:
	Vector2F() : x(0.0f), y(0.0f) {}
	Vector2F(F32 value) : x(value), y(value) {}
	Vector2F(F32 value1, F32 value2) : x(value1), y(value2) {}
	Vector2F(std::initializer_list<F32> list);
	~Vector2F() {}

	Vector2F operator=(const std::initializer_list<F32>& list);
	F32& operator[](UI32 index) const;

public:
	union
	{
		struct { F32 x, y; };
		struct { F32 a, b; };
		struct { F32 width, height; };
	};
};

Vector2F operator+(const Vector2F& lhs, const Vector2F& rhs);
Vector2F operator-(const Vector2F& lhs, const Vector2F& rhs);
Vector2F operator*(const Vector2F& lhs, const Vector2F& rhs);
Vector2F operator/(const Vector2F& lhs, const Vector2F& rhs);

Vector2F operator+(const Vector2F& lhs, const F32& value);
Vector2F operator-(const Vector2F& lhs, const F32& value);
Vector2F operator*(const Vector2F& lhs, const F32& value);
Vector2F operator/(const Vector2F& lhs, const F32& value);

B1 operator==(const Vector2F& lhs, const Vector2F& rhs);
B1 operator!=(const Vector2F& lhs, const Vector2F& rhs);
B1 operator<(const Vector2F& lhs, const Vector2F& rhs);
B1 operator<=(const Vector2F& lhs, const Vector2F& rhs);
B1 operator>(const Vector2F& lhs, const Vector2F& rhs);
B1 operator>=(const Vector2F& lhs, const Vector2F& rhs);

B1 operator&&(const Vector2F& lhs, const Vector2F& rhs);
B1 operator||(const Vector2F& lhs, const Vector2F& rhs);
B1 operator^(const Vector2F& lhs, const Vector2F& rhs);
B1 operator~(const Vector2F& rhs);
B1 operator!(const Vector2F& rhs);

#endif // !_DYNAMIK_VECTOR_2F_H
