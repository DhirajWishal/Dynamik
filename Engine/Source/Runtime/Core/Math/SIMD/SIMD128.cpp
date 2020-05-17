#include "dmkafx.h"
#include "SIMD128.h"

namespace Dynamik
{
	SIMD128::SIMD128()
		: myDataF(_mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f))
	{
	}

	SIMD128::SIMD128(F32 value)
		: myDataF(_mm_setr_ps(value, value, value, value))
	{
	}

	SIMD128::SIMD128(D64 value)
		: myDataD(_mm_setr_pd(value, value))
	{
	}

	SIMD128::SIMD128(I32 value)
		: myDataI(_mm_set1_epi32(value))
	{
	}

	SIMD128::SIMD128(F32 x, F32 y, F32 z, F32 a)
		: myDataF(_mm_setr_ps(x, y, z, a))
	{
	}

	SIMD128::SIMD128(D64 x, D64 y)
		: myDataD(_mm_setr_pd(x, y))
	{
	}

	SIMD128::SIMD128(I32 x, I32 y, I32 z, I32 a)
		: myDataI(_mm_setr_epi32(x, y, z, a))
	{
	}

	SIMD128::SIMD128(const SIMD128& other)
		: myDataF(other.myDataF)
	{
	}

	SIMD128::SIMD128(const Vector3F& other)
		: myDataF(_mm_setr_ps(other.x, other.y, other.z, other.a))
	{
	}

	SIMD128::SIMD128(const Vector4F& other)
		: myDataF(_mm_setr_ps(other.r, other.g, other.b, other.a))
	{
	}

	Vector3F SIMD128::toVec3F()
	{
		Vector3F _vector;
		storeAlign((F32*)&_vector);

		return _vector;
	}

	Vector4F SIMD128::toVec4F()
	{
		Vector4F _vector;
		storeAlign((F32*)&_vector);

		return _vector;
	}

	void SIMD128::load(const F32* address)
	{
		myDataF = _mm_loadu_ps(address);
	}

	void SIMD128::load(const D64* address)
	{
		myDataD = _mm_loadu_pd(address);
	}

	void SIMD128::load(const I32* address)
	{
		myDataI = _mm_loadu_si32(address);
	}

	void SIMD128::loadAlign(const F32* address)
	{
		myDataF = _mm_load_ps(address);
	}

	void SIMD128::loadAlign(const D64* address)
	{
		myDataD = _mm_load_pd(address);
	}

	void SIMD128::store(F32* address)
	{
		_mm_storeu_ps(address, myDataF);
	}

	void SIMD128::store(D64* address)
	{
		_mm_storeu_pd(address, myDataD);
	}

	void SIMD128::store(I32* address)
	{
		_mm_storeu_si32(address, myDataI);
	}

	void SIMD128::storeAlign(F32* address)
	{
		_mm_store_ps(address, myDataF);
	}
	
	void SIMD128::storeAlign(D64* address)
	{
		_mm_store_pd(address, myDataD);
	}
}