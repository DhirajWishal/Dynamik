// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Maths/Matrix/Matrix44.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Memory/Functions.h"
#include "Core/Types/Utilities.h"

namespace DMK
{
	Matrix44::Matrix44()
		: r(0.0f), g(0.0f), b(0.0f), a(0.0f)
	{
	}

	Matrix44::Matrix44(float value)
		:
		r(value, 0.0f, 0.0f, 0.0f),
		g(0.0f, value, 0.0f, 0.0f),
		b(0.0f, 0.0f, value, 0.0f),
		a(0.0f, 0.0f, 0.0f, value)
	{
	}

	Matrix44::Matrix44(Vector4 vec1, Vector4 vec2, Vector4 vec3, Vector4 vec4)
		: r(vec1), g(vec2), b(vec3), a(vec4)
	{
	}

	Matrix44::Matrix44(
		float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p)
		: r(a, b, c, d), g(e, f, g, h), b(i, j, k, l), a(m, n, o, p)
	{
	}

	Matrix44::Matrix44(const Matrix44& other)
		: r(other.r), g(other.g), b(other.b), a(other.a)
	{
	}

	Matrix44::Matrix44(std::initializer_list<float> list)
		: r(0.0f), g(0.0f), b(0.0f), a(0.0f)
	{
		if ((list.size() > 16) || (list.size() < 16))
			DMK_LOG_ERROR(TEXT("The size of the provided list does not match the current Matrix size!"));

		MemoryFunctions::MoveData(this, Cast<const void*>(list.begin()), list.size() * sizeof(float));
	}

	Matrix44 Matrix44::operator=(const Matrix44& other)
	{
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		this->a = other.a;

		return *this;
	}

	const Vector4 Matrix44::operator[](UI32 index) const
	{
		return (&this->r)[index];
	}

	Vector4& Matrix44::operator[](UI32 index)
	{
		return (&this->r)[index];
	}

	Matrix44& Matrix44::operator*(const float& value)
	{
		this->r *= value;
		this->g *= value;
		this->b *= value;
		this->a *= value;

		return *this;
	}

	Vector4 Matrix44::operator*(const Vector4& other)
	{
		return {
			(this->r[0] * other[0]) + (this->r[1] * other[1]) + (this->r[2] * other[2]) + (this->r[3] * other[3]),
			(this->g[0] * other[0]) + (this->g[1] * other[1]) + (this->g[2] * other[2]) + (this->g[3] * other[3]),
			(this->b[0] * other[0]) + (this->b[1] * other[1]) + (this->b[2] * other[2]) + (this->b[3] * other[3]),
			(this->a[0] * other[0]) + (this->a[1] * other[1]) + (this->a[2] * other[2]) + (this->a[3] * other[3])
		};
	}

	Matrix44& Matrix44::operator*(const Matrix44& other)
	{
		this->r = ((*this)[0] * other[0][0]) + ((*this)[1] * other[0][1]) + ((*this)[2] * other[0][2]) + ((*this)[3] * other[0][3]);
		this->g = ((*this)[0] * other[1][0]) + ((*this)[1] * other[1][1]) + ((*this)[2] * other[1][2]) + ((*this)[3] * other[1][3]);
		this->b = ((*this)[0] * other[2][0]) + ((*this)[1] * other[2][1]) + ((*this)[2] * other[2][2]) + ((*this)[3] * other[2][3]);
		this->a = ((*this)[0] * other[3][0]) + ((*this)[1] * other[3][1]) + ((*this)[2] * other[3][2]) + ((*this)[3] * other[3][3]);

		return *this;
	}

	Matrix44 operator*(const Matrix44& lhs, const float& rhs)
	{
		return Matrix44(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
	}
}