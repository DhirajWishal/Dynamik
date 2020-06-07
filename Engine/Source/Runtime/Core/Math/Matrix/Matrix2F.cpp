#include "dmkafx.h"
#include "Matrix2F.h"

#include "../SIMD/SIMD128.h"

namespace Dynamik
{
	Matrix2F::Matrix2F()
		: x(0.0f), y(0.0f)
	{
	}

	Matrix2F::Matrix2F(F32 value)
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
		F32 a, F32 b, 
		F32 c, F32 d)
		:
		x(a, b), y(c, d)
	{
	}

	Matrix2F::Matrix2F(const Matrix2F& other)
		: r(other.r), g(other.g)
	{
	}

	Matrix2F::Matrix2F(std::initializer_list<F32> list)
	{
		if ((list.size() > 4) || (list.size() < 4))
			DMK_ERROR_BOX("The size of the provided list does not match the current Matrix size!");

		DMKMemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(F32));
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
}