// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "SIMD512.h"

namespace Dynamik
{
	SIMD512::SIMD512() 
		: myDataF(_mm512_set1_ps(0.0f))
	{
	}
	
	SIMD512::SIMD512(F32 value) 
		: myDataF(_mm512_set1_ps(value))
	{
	}

	SIMD512::SIMD512(D64 value) 
		: myDataD(_mm512_set1_pd(value))
	{
	}
	
	SIMD512::SIMD512(I32 value) 
		: myDataI(_mm512_set1_epi32(value))
	{
	}

	SIMD512::SIMD512(
		F32 a, F32 b, F32 c, F32 d,
		F32 e, F32 f, F32 g, F32 h,
		F32 i, F32 j, F32 k, F32 l,
		F32 m, F32 n, F32 o, F32 p)
		: myDataF(_mm512_setr_ps(
			a, b, c, d, e, f, g, h,
			i, j, k, l, m, n, o, p))
	{
	}

	SIMD512::SIMD512(
		D64 a, D64 b, D64 c, D64 d,
		D64 e, D64 f, D64 g, D64 h)
		: myDataD(_mm512_setr_pd(
			a, b, c, d, e, f, g, h))
	{
	}

	SIMD512::SIMD512(
		I32 a, I32 b, I32 c, I32 d,
		I32 e, I32 f, I32 g, I32 h,
		I32 i, I32 j, I32 k, I32 l,
		I32 m, I32 n, I32 o, I32 p)
		: myDataI(_mm512_setr_epi32(
			a, b, c, d, e, f, g, h,
			i, j, k, l, m, n, o, p))
	{
	}
	
	SIMD512::SIMD512(const SIMD512& other)
		: myDataD(other.myDataD)
	{
	}

	Matrix4F SIMD512::toMat4F()
	{
		Matrix4F _matrix;
		store((F32*)&_matrix);

		return _matrix;
	}

	Matrix3F SIMD512::toMat3F()
	{
		Matrix3F _matrix;
		store((F32*)&_matrix);

		return _matrix;
	}

	void SIMD512::load(const F32* address)
	{
		myDataF = _mm512_loadu_ps(address);
	}

	void SIMD512::load(const D64* address)
	{
		myDataD = _mm512_loadu_pd(address);
	}

	void SIMD512::loadAlign(const F32* address)
	{
		myDataF = _mm512_load_ps(address);
	}

	void SIMD512::loadAlign(const D64* address)
	{
		myDataD = _mm512_load_pd(address);
	}

	void SIMD512::store(F32* address)
	{
		_mm512_storeu_ps(address, myDataF);
	}

	void SIMD512::store(D64* address)
	{
		_mm512_storeu_pd(address, myDataD);
	}

	void SIMD512::storeAlign(F32* address)
	{
		_mm512_store_ps(address, myDataF);
	}

	void SIMD512::storeAlign(D64* address)
	{
		_mm512_store_pd(address, myDataD);
	}
}