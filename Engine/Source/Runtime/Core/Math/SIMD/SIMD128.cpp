#include "dmkafx.h"
#include "SIMD128.h"

namespace Dynamik
{
	SIMD128::SIMD128() : myData(_mm_setr_ps(0.0f, 0.0f, 0.0f, 0.0f))
	{
	}

	SIMD128::SIMD128(F32 value) : myData(_mm_setr_ps(value, value, value, value))
	{
	}

	SIMD128::SIMD128(I32 value) : myData(_mm_castsi128_ps(_mm_set1_epi32(value)))
	{
	}

	SIMD128::SIMD128(F32 x, F32 y, F32 z, F32 a) : myData(_mm_setr_ps(x, y, z, a))
	{
	}

	SIMD128::SIMD128(const SIMD128& other) : myData(other.myData)
	{
	}

	SIMD128::SIMD128(const Vector3D& other) : myData(_mm_setr_ps(other.x, other.y, other.z, other.a))
	{
	}

	Vector3D SIMD128::toVec3()
	{
		Vector3D _vector;
		storeAlign((F32*)&_vector);

		return _vector;
	}

	void SIMD128::load(const F32* address)
	{
		myData = _mm_loadu_ps(address);
	}

	void SIMD128::loadAlign(const F32* address)
	{
		myData = _mm_load_ps(address);
	}

	void SIMD128::store(F32* address)
	{
		_mm_storeu_ps(address, myData);
	}

	void SIMD128::storeAlign(F32* address)
	{
		_mm_store_ps(address, myData);
	}
}