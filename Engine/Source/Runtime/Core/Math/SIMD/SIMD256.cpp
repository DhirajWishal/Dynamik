#include "dmkafx.h"
#include "SIMD256.h"

namespace Dynamik
{
	SIMD256::SIMD256()
		: myDataF(_mm256_set1_ps(0.0f))
	{
	}
	
	SIMD256::SIMD256(F32 value) : myDataF(_mm256_set1_ps(value))
	{
	}

	SIMD256::SIMD256(D64 value) : myDataD(_mm256_set1_pd(value))
	{
	}

	SIMD256::SIMD256(I32 value) : myDataI(_mm256_set1_epi32(value))
	{
	}

	SIMD256::SIMD256(F32 a, F32 b, F32 c, F32 d, F32 e, F32 f, F32 g, F32 h)
		: myDataF(_mm256_setr_ps(a, b, c, d, e, f, g, h))
	{
	}

	SIMD256::SIMD256(D64 x, D64 y, D64 z, D64 a)
		: myDataD(_mm256_setr_pd(x, y, z, a))
	{
	}

	SIMD256::SIMD256(I32 a, I32 b, I32 c, I32 d, I32 e, I32 f, I32 g, I32 h)
		: myDataI(_mm256_setr_epi32(a, b, c, d, e, f, g, h))
	{
	}

	SIMD256::SIMD256(const SIMD256& other)
		: myDataD(other.myDataD)
	{
	}

	SIMD256::SIMD256(const Vector3D& other)
		: myDataD(_mm256_setr_pd(other.x, other.y, other.z, other.a))
	{
	}

	SIMD256::SIMD256(const Vector4D& other)
		: myDataD(_mm256_setr_pd(other.x, other.y, other.z, other.a))
	{
	}

	Vector3D SIMD256::toVec3D()
	{
		Vector3D _vector;
		store((D64*)&_vector);

		return _vector;
	}

	Vector4D SIMD256::toVec4D()
	{
		Vector4D _vector;
		store((D64*)&_vector);

		return _vector;
	}

	void SIMD256::load(const F32* address)
	{
		myDataF = _mm256_loadu_ps(address);
	}

	void SIMD256::load(const D64* address)
	{
		myDataD = _mm256_loadu_pd(address);
	}

	void SIMD256::loadAlign(const F32* address)
	{
		myDataF = _mm256_load_ps(address);
	}

	void SIMD256::loadAlign(const D64* address)
	{
		myDataD = _mm256_load_pd(address);
	}

	void SIMD256::store(F32* address)
	{
		_mm256_storeu_ps(address, myDataF);
	}

	void SIMD256::store(D64* address)
	{
		_mm256_storeu_pd(address, myDataD);
	}

	void SIMD256::storeAlign(F32* address)
	{
		_mm256_store_ps(address, myDataF);
	}

	void SIMD256::storeAlign(D64* address)
	{
		_mm256_store_pd(address, myDataD);
	}
}