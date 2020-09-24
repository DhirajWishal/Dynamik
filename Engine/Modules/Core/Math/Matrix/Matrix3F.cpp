// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Matrix3F.h"

Matrix3F::Matrix3F()
	: r(0.0f), g(0.0f), b(0.0f)
{
}

Matrix3F::Matrix3F(F32 value)
	:
	r(value, 0.0f, 0.0f),
	g(0.0f, value, 0.0f),
	b(0.0f, 0.0f, value)
{
}

Matrix3F::Matrix3F(Vector3F vec1, Vector3F vec2, Vector3F vec3)
	: r(vec1), g(vec2), b(vec3)
{
}

Matrix3F::Matrix3F(
	F32 a, F32 b, F32 c,
	F32 d, F32 e, F32 f,
	F32 g, F32 h, F32 i)
	:
	x(a, b, c), y(d, e, f), z(g, h, i)
{
}

Matrix3F::Matrix3F(const Matrix3F& other)
	: r(other.r), g(other.g), b(other.b)
{
}

Matrix3F::Matrix3F(std::initializer_list<F32> list)
{
	if ((list.size() > 9) || (list.size() < 9))
		DMK_ERROR_BOX("The size of the provided list does not match the current Matrix size!");

	DMKMemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(F32));
}

Matrix3F Matrix3F::operator=(const Matrix3F& other)
{
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;

	return *this;
}

Vector3F& Matrix3F::operator[](UI32 index) const
{
	return ((Vector3F*)this)[index];
}
