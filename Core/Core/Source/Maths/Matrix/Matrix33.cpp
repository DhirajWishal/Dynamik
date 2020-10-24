// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Maths/Matrix/Matrix33.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Memory/Functions.h"

namespace DMK
{
	Matrix33::Matrix33()
		: r(0.0f), g(0.0f), b(0.0f)
	{
	}

	Matrix33::Matrix33(float value)
		:
		r(value, 0.0f, 0.0f),
		g(0.0f, value, 0.0f),
		b(0.0f, 0.0f, value)
	{
	}

	Matrix33::Matrix33(Vector3 vec1, Vector3 vec2, Vector3 vec3)
		: r(vec1), g(vec2), b(vec3)
	{
	}

	Matrix33::Matrix33(
		float a, float b, float c,
		float d, float e, float f,
		float g, float h, float i)
		:
		x(a, b, c), y(d, e, f), z(g, h, i)
	{
	}

	Matrix33::Matrix33(const Matrix33& other)
		: r(other.r), g(other.g), b(other.b)
	{
	}

	Matrix33::Matrix33(std::initializer_list<float> list)
		: r(0.0f), g(0.0f), b(0.0f)
	{
		if ((list.size() > 9) || (list.size() < 9))
			Logger::LogError(TEXT("The size of the provided list does not match the current Matrix size!"));

		MemoryFunctions::MoveData(this, (void*)list.begin(), list.size() * sizeof(float));
	}

	Matrix33 Matrix33::operator=(const Matrix33& other)
	{
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;

		return *this;
	}

	Vector3& Matrix33::operator[](UI32 index) const
	{
		return ((Vector3*)this)[index];
	}

	Matrix33& Matrix33::operator*(const float& value)
	{
		this->r *= value;
		this->g *= value;
		this->b *= value;

		return *this;
	}

	Vector3 Matrix33::operator*(const Vector3& other)
	{
		return {
			(this->r[0] * other[0]) + (this->r[1] * other[1]) + (this->r[2] * other[2]),
			(this->g[0] * other[0]) + (this->g[1] * other[1]) + (this->g[2] * other[2]),
			(this->b[0] * other[0]) + (this->b[1] * other[1]) + (this->b[2] * other[2])
		};
	}

	Matrix33& Matrix33::operator*(const Matrix33& other)
	{
		this->r = ((*this)[0] * other[0][0]) + ((*this)[1] * other[0][1]) + ((*this)[2] * other[0][2]);
		this->g = ((*this)[0] * other[1][0]) + ((*this)[1] * other[1][1]) + ((*this)[2] * other[1][2]);
		this->b = ((*this)[0] * other[2][0]) + ((*this)[1] * other[2][1]) + ((*this)[2] * other[2][2]);

		return *this;
	}
}