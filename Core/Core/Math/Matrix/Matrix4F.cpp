// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Matrix4F.h"

Matrix4F::Matrix4F()
	: r(0.0f), g(0.0f), b(0.0f), a(0.0f)
{
}

Matrix4F::Matrix4F(float value)
	:
	r(value, 0.0f, 0.0f, 0.0f),
	g(0.0f, value, 0.0f, 0.0f),
	b(0.0f, 0.0f, value, 0.0f),
	a(0.0f, 0.0f, 0.0f, value)
{
}

Matrix4F::Matrix4F(Vector4F vec1, Vector4F vec2, Vector4F vec3, Vector4F vec4)
	: r(vec1), g(vec2), b(vec3), a(vec4)
{
}

Matrix4F::Matrix4F(
	float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p)
	: r(a, b, c, d), g(e, f, g, h), b(i, j, k, l), a(m, n, o, p)
{
}

Matrix4F::Matrix4F(const Matrix4F& other)
	: r(other.r), g(other.g), b(other.b), a(other.a)
{
}

Matrix4F::Matrix4F(std::initializer_list<float> list)
{
	if ((list.size() > 16) || (list.size() < 16))
		DMK_ERROR_BOX("The size of the provided list does not match the current Matrix size!");

	DMKMemoryFunctions::moveData(this, (void*)list.begin(), list.size() * sizeof(float));
}

Matrix4F Matrix4F::operator=(const Matrix4F& other)
{
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	this->a = other.a;

	return *this;
}

Vector4F& Matrix4F::operator[](UI32 index) const
{
	return ((Vector4F*)this)[index];
}

Matrix4F operator*(const Matrix4F& lhs, const float& rhs)
{
	return Matrix4F(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
}

Matrix4F Matrix4F::Identity = Matrix4F(1.0f);
