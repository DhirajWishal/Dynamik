#include "dmkafx.h"
#include "Matrix4F.h"

#include "../SIMD/SIMDFunctions.h"

namespace Dynamik
{
	Matrix4F::Matrix4F()
		: r(0.0f), g(0.0f), b(0.0f), a(0.0f)
	{
	}

	Matrix4F::Matrix4F(F32 value)
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
		F32 a, F32 b, F32 c, F32 d,
		F32 e, F32 f, F32 g, F32 h,
		F32 i, F32 j, F32 k, F32 l,
		F32 m, F32 n, F32 o, F32 p)
		: r(a, b, c, d), g(e, f, g, h), b(i, j, k, l), a(m, n, o, p)
	{
	}

	Matrix4F::Matrix4F(const Matrix4F& other)
		: r(other.r), g(other.g), b(other.b), a(other.a)
	{
	}

	Matrix4F::Matrix4F(std::initializer_list<F32> list)
	{
		if ((list.size() > 16) || (list.size() < 16))
			DMK_ERROR_BOX("The size of the provided list does not match the current Matrix size!");

		MemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(F32));
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
}