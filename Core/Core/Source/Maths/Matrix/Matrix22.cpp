// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Maths/Matrix/Matrix22.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Memory/Functions.h"

namespace DMK
{
	Matrix22::Matrix22()
		: x(0.0f), y(0.0f)
	{
	}

	Matrix22::Matrix22(float value)
		:
		x(value, 0.0f),
		y(0.0f, value)
	{
	}

	Matrix22::Matrix22(Vector2 vec1, Vector2 vec2)
		: x(vec1), y(vec2)
	{
	}

	Matrix22::Matrix22(
		float a, float b,
		float c, float d)
		:
		x(a, b), y(c, d)
	{
	}

	Matrix22::Matrix22(const Matrix22& other)
		: r(other.r), g(other.g)
	{
	}

	Matrix22::Matrix22(std::initializer_list<float> list)
		: x(0.0f), y(0.0f)
	{
		if ((list.size() > 4) || (list.size() < 4))
			Logger::LogError(TEXT("The size of the provided list does not match the current Matrix size!"));

		MemoryFunctions::MoveData(this, (void*)list.begin(), list.size() * sizeof(float));
	}

	Matrix22 Matrix22::operator=(const Matrix22& other)
	{
		this->r = other.r;
		this->g = other.g;

		return *this;
	}

	Vector2& Matrix22::operator[](UI32 index) const
	{
		return ((Vector2*)this)[index];
	}

	Matrix22& Matrix22::operator*(const float& value)
	{
		this->r *= value;
		this->g *= value;

		return *this;
	}

	Vector2 Matrix22::operator*(const Vector2& other)
	{
		return { (this->r[0] * other[0]) + (this->r[1] * other[1]), (this->g[0] * other[0]) + (this->g[1] * other[1]) };
	}

	Matrix22& Matrix22::operator*(const Matrix22& other)
	{
		this->r = ((*this)[0] * other[0][0]) + ((*this)[1] * other[0][1]);
		this->g = ((*this)[0] * other[1][0]) + ((*this)[1] * other[1][1]);

		return *this;
	}
}