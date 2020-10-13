// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Vector2F.h"

Vector2F::Vector2F(std::initializer_list<float> list)
{
	if ((list.size() > 2) || (list.size() < 2))
		DMK_ERROR_BOX("The size of the provided list does not match the current Vector size! Expected size is 2.");

	DMKMemoryFunctions::moveData(this, (void*)list.begin(), list.size() * sizeof(float));
}

Vector2F Vector2F::operator=(const std::initializer_list<float>& list)
{
	if ((list.size() > 2) || (list.size() < 2))
		DMK_ERROR_BOX("The size of the provided list does not match the current Vector size! Expected size is 2.");

	DMKMemoryFunctions::moveData(this, (void*)list.begin(), list.size() * sizeof(float));

	return *this;
}

float& Vector2F::operator[](UI32 index) const
{
	return ((float*)this)[index];
}

Vector2F operator+(const Vector2F& lhs, const Vector2F& rhs)
{
	return Vector2F(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2F operator-(const Vector2F& lhs, const Vector2F& rhs)
{
	return Vector2F(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2F operator*(const Vector2F& lhs, const Vector2F& rhs)
{
	return Vector2F(lhs.x * rhs.x, lhs.y * rhs.y);
}

Vector2F operator/(const Vector2F& lhs, const Vector2F& rhs)
{
	return Vector2F(lhs.x / rhs.x, lhs.y / rhs.y);
}

Vector2F operator+(const Vector2F& lhs, const float& value)
{
	return lhs + Vector2F(value);
}

Vector2F operator-(const Vector2F& lhs, const float& value)
{
	return lhs - Vector2F(value);
}

Vector2F operator*(const Vector2F& lhs, const float& value)
{
	return lhs * Vector2F(value);
}

Vector2F operator/(const Vector2F& lhs, const float& value)
{
	return lhs / Vector2F(value);
}

bool operator==(const Vector2F& lhs, const Vector2F& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const Vector2F& lhs, const Vector2F& rhs)
{
	return (lhs.x != rhs.x) || (lhs.y != rhs.y);
}

bool operator<(const Vector2F& lhs, const Vector2F& rhs)
{
	return (lhs.x < rhs.x) || (lhs.y < rhs.y);
}

bool operator<=(const Vector2F& lhs, const Vector2F& rhs)
{
	return (lhs.x <= rhs.x) || (lhs.y <= rhs.y);
}

bool operator>(const Vector2F& lhs, const Vector2F& rhs)
{
	return (lhs.x > rhs.x) || (lhs.y > rhs.y);
}

bool operator>=(const Vector2F& lhs, const Vector2F& rhs)
{
	return (lhs.x >= rhs.x) || (lhs.y >= rhs.y);
}

bool operator&&(const Vector2F& lhs, const Vector2F& rhs)
{
	return (lhs.x && rhs.x) && (lhs.y && rhs.y);
}

bool operator||(const Vector2F& lhs, const Vector2F& rhs)
{
	return (lhs.x || rhs.x) || (lhs.y || rhs.y);
}

bool operator^(const Vector2F& lhs, const Vector2F& rhs)
{
	return (lhs.x || rhs.x) && (lhs.y || rhs.y);
}

bool operator~(const Vector2F& rhs)
{
	return (rhs.x > 0) && (rhs.y > 0);
}

bool operator!(const Vector2F& rhs)
{
	return (rhs.x != 0) && (rhs.y != 0);
}
