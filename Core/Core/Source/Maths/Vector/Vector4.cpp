// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Maths/Vector/Vector4.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Memory/Functions.h"
#include "Core/Maths/IncludeSIMD.h"
#include "Core/Types/Utilities.h"

namespace DMK
{
	Vector4::Vector4(std::initializer_list<float> list)
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
		if ((list.size() > 4) || (list.size() < 4))
			Logger::LogError(TEXT("The size of the provided list does not match the current Vector size! Expected size is 4."));

		MemoryFunctions::MoveData(this, (void*)list.begin(), list.size() * sizeof(float));
	}

	Vector4::Vector4(const float* ptr)
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
		MemoryFunctions::MoveData(this, (void*)ptr, sizeof(float) * 4);
	}

	Vector4 Vector4::operator=(const std::initializer_list<float>& list)
	{
		if ((list.size() > 4) || (list.size() < 4))
			Logger::LogError(TEXT("The size of the provided list does not match the current Vector size! Expected size is 4."));

		MemoryFunctions::MoveData(this, (void*)list.begin(), list.size() * sizeof(float));

		return *this;
	}

	float& Vector4::operator[](UI32 index) const
	{
		return ((float*)this)[index];
	}

	Vector4::operator float* () const
	{
		return (float*)this;
	}

	Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
	{
		return (const float*)&_mm_add_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	}

	Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
	{
		return (const float*)&_mm_sub_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	}

	Vector4 operator*(const Vector4& lhs, const Vector4& rhs)
	{
		return (const float*)&_mm_mul_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	}

	Vector4 operator/(const Vector4& lhs, const Vector4& rhs)
	{
		return (const float*)&_mm_div_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
	}

	Vector4 operator+(const Vector4& lhs, const float& value)
	{
		return lhs + Vector4(value);
	}

	Vector4 operator-(const Vector4& lhs, const float& value)
	{
		return lhs - Vector4(value);
	}

	Vector4 operator*(const Vector4& lhs, const float& value)
	{
		return lhs * Vector4(value);
	}

	Vector4 operator/(const Vector4& lhs, const float& value)
	{
		return lhs / +Vector4(value);
	}

	bool operator==(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_cmpeq_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator!=(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_cmpneq_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator<(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_cmplt_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
		return ((vec.r) || (vec.g) || (vec.b) || (vec.a));
	}

	bool operator<=(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_cmple_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator>(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_cmpgt_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
		return ((vec.r) || (vec.g) || (vec.b) || (vec.a));
	}

	bool operator>=(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_cmpge_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator&&(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_and_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator||(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_or_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator^(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_or_ps(_mm_load_ps(lhs), _mm_load_ps(rhs));
		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator~(const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_or_ps(_mm_load_ps(rhs), _mm_load_ps(Vector4(-1.0f)));
		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator!(const Vector4& rhs)
	{
		Vector4 vec = (const float*)&_mm_or_ps(_mm_load_ps(rhs), _mm_load_ps(Vector4(0.0f)));
		return ((vec.r == 0) && (vec.g == 0) && (vec.b == 0) && (vec.a == 0));
	}
}