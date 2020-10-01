// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Matrix2F.h"

Matrix2F::Matrix2F()
	: x(0.0f), y(0.0f)
{
}

Matrix2F::Matrix2F(float value)
	:
	x(value, 0.0f),
	y(0.0f, value)
{
}

Matrix2F::Matrix2F(Vector2F vec1, Vector2F vec2)
	: x(vec1), y(vec2)
{
}

Matrix2F::Matrix2F(
	float a, float b,
	float c, float d)
	:
	x(a, b), y(c, d)
{
}

Matrix2F::Matrix2F(const Matrix2F& other)
	: r(other.r), g(other.g)
{
}

Matrix2F::Matrix2F(std::initializer_list<float> list)
{
	if ((list.size() > 4) || (list.size() < 4))
		DMK_ERROR_BOX("The size of the provided list does not match the current Matrix size!");

	DMKMemoryFunctions::moveData(this, (void*)list.begin(), list.size() * sizeof(float));
}

Matrix2F Matrix2F::operator=(const Matrix2F& other)
{
	this->r = other.r;
	this->g = other.g;

	return *this;
}

Vector2F& Matrix2F::operator[](UI32 index) const
{
	return ((Vector2F*)this)[index];
}
