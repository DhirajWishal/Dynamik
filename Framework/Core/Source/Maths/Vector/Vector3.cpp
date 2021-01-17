// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Maths/Vector/Vector3.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Memory/Functions.h"
#include "Core/Maths/IncludeSIMD.h"
#include "Core/Types/Utilities.h"

namespace DMK
{
	Vector3::Vector3(std::initializer_list<float> list)
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
		if ((list.size() > 3) || (list.size() < 3))
			DMK_LOG_ERROR(TEXT("The size of the provided list does not match the current Vector size!"));

		MemoryFunctions::MoveData(this, Cast<const void*>(list.begin()), list.size() * sizeof(float));
		w = 0.0f;
	}

	Vector3::Vector3(const float* ptr)
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
		MemoryFunctions::MoveData(this, Cast<const void*>(ptr), sizeof(float) * 3);
	}

	Vector3 Vector3::operator=(const std::initializer_list<float>& list)
	{
		if ((list.size() > 3) || (list.size() < 3))
			DMK_LOG_ERROR(TEXT("The size of the provided list does not match the current Vector size!"));

		MemoryFunctions::MoveData(this, Cast<const void*>(list.begin()), list.size() * sizeof(float));
		this->w = 0.0f;
		return *this;
	}

	const float Vector3::operator[](UI32 index) const
	{
		return (operator const float* ())[index];
	}

	float& Vector3::operator[](UI32 index)
	{
		return const_cast<float&>((operator const float* ())[index]);
	}

	Vector3::operator const float* () const
	{
		return &this->x;
	}

	Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_add_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return vec;
	}

	Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_sub_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return vec;
	}

	Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_mul_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return vec;
	}

	Vector3 operator/(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_div_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return vec;
	}

	Vector3 operator+(const Vector3& lhs, const float& value)
	{
		return lhs + Vector3(value);
	}

	Vector3 operator-(const Vector3& lhs, const float& value)
	{
		return lhs - Vector3(value);
	}

	Vector3 operator*(const Vector3& lhs, const float& value)
	{
		return lhs * Vector3(value);
	}

	Vector3 operator/(const Vector3& lhs, const float& value)
	{
		return lhs / Vector3(value);
	}

	bool operator==(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmpeq_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator!=(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmpneq_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator<(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmplt_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) || (vec.g) || (vec.b) || (vec.a));
	}

	bool operator<=(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmple_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator>(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmpgt_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) || (vec.g) || (vec.b) || (vec.a));
	}

	bool operator>=(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_cmpge_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator&&(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_and_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator||(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_or_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator^(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_or_ps(_mm_load_ps(&lhs.x), _mm_load_ps(&rhs.x)));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator~(const Vector3& rhs)
	{
		Vector3 vec = 0.0f;
		_mm_store_ps(&vec.x, _mm_or_ps(_mm_load_ps(&rhs.x), _mm_load_ps(Vector3(-1.0f))));

		return ((vec.r) && (vec.g) && (vec.b) && (vec.a));
	}

	bool operator!(const Vector3& rhs)
	{
		Vector3 vec = {};
		_mm_store_ps(&vec.x, _mm_or_ps(_mm_load_ps(&rhs.x), _mm_load_ps(Vector3(0.0f))));

		return ((vec.r == 0) && (vec.g == 0) && (vec.b == 0) && (vec.a == 0));
	}
}