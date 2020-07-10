// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Vector2F.h"

namespace Dynamik
{
	Vector2F::Vector2F(std::initializer_list<F32> list) 
	{
		if ((list.size() > 2) || (list.size() < 2))
			DMK_ERROR_BOX("The size of the provided list does not match the current Vector size! Expected size is 2.");

		DMKMemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(F32));
	}

	Vector2F Vector2F::operator=(const std::initializer_list<F32>& list)
	{
		if ((list.size() > 2) || (list.size() < 2))
			DMK_ERROR_BOX("The size of the provided list does not match the current Vector size! Expected size is 2.");

		DMKMemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(F32));

		return *this;
	}

	F32& Vector2F::operator[](UI32 index) const 
	{
		return ((F32*)this)[index];
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

	Vector2F operator+(const Vector2F& lhs, const F32& value)
	{
		return lhs + Vector2F(value);
	}

	Vector2F operator-(const Vector2F& lhs, const F32& value)
	{
		return lhs - Vector2F(value);
	}

	Vector2F operator*(const Vector2F& lhs, const F32& value)
	{
		return lhs * Vector2F(value);
	}

	Vector2F operator/(const Vector2F& lhs, const F32& value)
	{
		return lhs / Vector2F(value);
	}

	B1 operator==(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	B1 operator!=(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x != rhs.x) || (lhs.y != rhs.y);
	}

	B1 operator<(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x < rhs.x) || (lhs.y < rhs.y);
	}

	B1 operator<=(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x <= rhs.x) || (lhs.y <= rhs.y);
	}

	B1 operator>(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x > rhs.x) || (lhs.y > rhs.y);
	}

	B1 operator>=(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x >= rhs.x) || (lhs.y >= rhs.y);
	}

	B1 operator&&(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x && rhs.x) && (lhs.y && rhs.y);
	}

	B1 operator||(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x || rhs.x) || (lhs.y || rhs.y);
	}

	B1 operator^(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x || rhs.x) && (lhs.y || rhs.y);
	}

	B1 operator~(const Vector2F& rhs)
	{
		return (rhs.x > 0) && (rhs.y > 0);
	}

	B1 operator!(const Vector2F& rhs)
	{
		return (rhs.x != 0) && (rhs.y != 0);
	}
}