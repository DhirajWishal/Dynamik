// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Vector3F.h"

#include "../IncludeSIMD.h"

Vector3F::Vector3F(std::initializer_list<float> list)
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
	if ((list.size() > 3) || (list.size() < 3))
		DMK_ERROR_BOX("The size of the provided list does not match the current Vector size!");

	DMKMemoryFunctions::moveData(this, (void*)list.begin(), list.size() * sizeof(float));
	w = 0.0f;
}

Vector3F::Vector3F(const float* ptr)
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
	DMKMemoryFunctions::moveData(this, (void*)ptr, sizeof(float) * 3);
}

Vector3F Vector3F::operator=(const std::initializer_list<float>& list)
{
	if ((list.size() > 3) || (list.size() < 3))
		DMK_ERROR_BOX("The size of the provided list does not match the current Vector size!");

	DMKMemoryFunctions::moveData(this, (void*)list.begin(), list.size() * sizeof(float));
	this->w = 0.0f;
	return *this;
}

float& Vector3F::operator[](UI32 index) const
{
	return ((float*)this)[index];
}

Vector3F::operator float* () const
{
	return Cast<float*>(&this->x);
}

Vector3F operator+(const Vector3F& lhs, const Vector3F& rhs)
{
	return (const float*)&_mm_add_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
}

Vector3F operator-(const Vector3F& lhs, const Vector3F& rhs)
{
	return (const float*)&_mm_sub_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
}

Vector3F operator*(const Vector3F& lhs, const Vector3F& rhs)
{
	return (const float*)&_mm_mul_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
}

Vector3F operator/(const Vector3F& lhs, const Vector3F& rhs)
{
	return (const float*)&_mm_div_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
}

Vector3F operator+(const Vector3F& lhs, const float& value)
{
	return lhs + Vector3F(value);
}

Vector3F operator-(const Vector3F& lhs, const float& value)
{
	return lhs - Vector3F(value);
}

Vector3F operator*(const Vector3F& lhs, const float& value)
{
	return lhs * Vector3F(value);
}

Vector3F operator/(const Vector3F& lhs, const float& value)
{
	return lhs / Vector3F(value);
}

bool operator==(const Vector3F& lhs, const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_cmpeq_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator!=(const Vector3F& lhs, const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_cmpneq_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator<(const Vector3F& lhs, const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_cmplt_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
}

bool operator<=(const Vector3F& lhs, const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_cmple_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator>(const Vector3F& lhs, const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_cmpgt_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) || (vec.g != 0) || (vec.b != 0) || (vec.a != 0));
}

bool operator>=(const Vector3F& lhs, const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_cmpge_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator&&(const Vector3F& lhs, const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_and_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator||(const Vector3F& lhs, const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_or_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator^(const Vector3F& lhs, const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_or_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator~(const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_or_ps(_mm_load_ps(rhs), _mm_load_ps(Vector3F(-1.0f)));
	return ((vec.r != 0) && (vec.g != 0) && (vec.b != 0) && (vec.a != 0));
}

bool operator!(const Vector3F& rhs)
{
	Vector3F vec = (const float*)&_mm_or_ps(_mm_load_ps(rhs), _mm_load_ps(Vector3F(0.0f)));
	return ((vec.r == 0) && (vec.g == 0) && (vec.b == 0) && (vec.a == 0));
}
