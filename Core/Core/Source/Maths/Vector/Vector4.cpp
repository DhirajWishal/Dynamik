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

		MemoryFunctions::MoveData(this, Cast<const void*>(list.begin()), list.size() * sizeof(float));
	}

	Vector4::Vector4(const float* ptr)
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
		MemoryFunctions::MoveData(this, Cast<const void*>(ptr), sizeof(float) * 4);
	}

	Vector4 Vector4::operator=(const std::initializer_list<float>& list)
	{
		if ((list.size() > 4) || (list.size() < 4))
			Logger::LogError(TEXT("The size of the provided list does not match the current Vector size! Expected size is 4."));

		MemoryFunctions::MoveData(this, Cast<const void*>(list.begin()), list.size() * sizeof(float));

		return *this;
	}

	const float Vector4::operator[](UI32 index) const
	{
		return (operator const float* ())[index];
	}

	float& Vector4::operator[](UI32 index)
	{
		return const_cast<float&>((operator const float* ())[index]);
	}

	Vector4::operator const float* () const
	{
		return &this->x;
	}

	Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_add_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return vec;
	}

	Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_sub_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return vec;
	}

	Vector4 operator*(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_mul_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return vec;
	}

	Vector4 operator/(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_div_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return vec;
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
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmpeq_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator!=(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmpneq_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator<(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmplt_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) || (vec.g) || (vec.b) || (vec.a));
	}

	bool operator<=(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmple_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator>(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmpgt_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) || (vec.g) || (vec.b) || (vec.a));
	}

	bool operator>=(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmpge_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator&&(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_and_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator||(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_or_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator^(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_or_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator~(const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		Vector4 check = { -1.0f };
		_mm_store_ps(&vec.x, _mm_or_ps(_mm_load_ps(&rhs.x), _mm_load_ps(&check.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator!(const Vector4& rhs)
	{
		Vector4 vec = 0.0f;
		Vector4 check = { 0.0f };
		_mm_store_ps(&vec.x, _mm_or_ps(_mm_load_ps(&rhs.x), _mm_load_ps(&check.x)));

		return ((vec.r == 0) && (vec.g == 0) && (vec.b == 0) && (vec.a == 0));
	}
}