// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Vector4F.h"

#include "../IncludeSIMD.h"

Vector4F::Vector4F(std::initializer_list<float> list)
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
	if ((list.size() > 4) || (list.size() < 4))
		DMK_ERROR_BOX("The size of the provided list does not match the current Vector size! Expected size is 4.");

	DMKMemoryFunctions::moveData(this, (void*)list.begin(), list.size() * sizeof(float));
}

Vector4F::Vector4F(const float* ptr)
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
	DMKMemoryFunctions::moveData(this, (void*)ptr, sizeof(float) * 4);
}

Vector4F Vector4F::operator=(const std::initializer_list<float>& list)
{
	if ((list.size() > 4) || (list.size() < 4))
		DMK_ERROR_BOX("The size of the provided list does not match the current Vector size! Expected size is 4.");

	DMKMemoryFunctions::moveData(this, (void*)list.begin(), list.size() * sizeof(float));

	return *this;
}

float& Vector4F::operator[](UI32 index) const
{
	return ((float*)this)[index];
}

Vector4F::operator float* () const
{
	return (float*)this;
}

Vector4F operator+(const Vector4F& lhs, const Vector4F& rhs)
{
	return (const float*)&_mm_add_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
}

Vector4F operator-(const Vector4F& lhs, const Vector4F& rhs)
{
	return (const float*)&_mm_sub_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
}

Vector4F operator*(const Vector4F& lhs, const Vector4F& rhs)
{
	return (const float*)&_mm_mul_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
}

Vector4F operator/(const Vector4F& lhs, const Vector4F& rhs)
{
	return (const float*)&_mm_div_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
}

Vector4F operator+(const Vector4F& lhs, const float& value)
{
	return lhs + Vector4F(value);
}

Vector4F operator-(const Vector4F& lhs, const float& value)
{
	return lhs - Vector4F(value);
}

Vector4F operator*(const Vector4F& lhs, const float& value)
{
	return lhs * Vector4F(value);
}

Vector4F operator/(const Vector4F& lhs, const float& value)
{
	return lhs / +Vector4F(value);
}

bool operator==(const Vector4F& lhs, const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_cmpeq_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator!=(const Vector4F& lhs, const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_cmpneq_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator<(const Vector4F& lhs, const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_cmplt_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
}

bool operator<=(const Vector4F& lhs, const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_cmple_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator>(const Vector4F& lhs, const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_cmpgt_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
}

bool operator>=(const Vector4F& lhs, const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_cmpge_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator&&(const Vector4F& lhs, const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_and_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator||(const Vector4F& lhs, const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_or_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator^(const Vector4F& lhs, const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_or_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator~(const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_or_ps(_mm_load_ps(rhs), _mm_load_ps(Vector4F(-1.0f)));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator!(const Vector4F& rhs)
{
	Vector4F vec = (const float*)&_mm_or_ps(_mm_load_ps(rhs), _mm_load_ps(Vector4F(0.0f)));
	return ((vec.r == 0) && (vec.g == 0) && (vec.b == 0) && (vec.a == 0));
}
