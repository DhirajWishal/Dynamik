#pragma once
#ifndef _DYNAMIK_SIMD_256_H
#define _DYNAMIK_SIMD_256_H

/*
 Author:    Dhiraj Wishal
 Date:      16/05/2020
*/
#include "Base.h"
#include "Vector3D.h"
#include "Vector4D.h"

namespace Dynamik
{
	DMK_ALIGN_VEC3D class DMK_API Vector3D;
	DMK_ALIGN_VEC4D class DMK_API Vector4D;

	/*
	 256 bit SIMD container class (8 floats, 4 doubles).
	*/
	class DMK_API SIMD256 : public BaseSIMD {
	public:
		SIMD256();
		SIMD256(F32 value);
		SIMD256(D64 value);
		SIMD256(I32 value);
		SIMD256(
			F32 a, F32 b, F32 c, F32 d,
			F32 e, F32 f, F32 g, F32 h);
		SIMD256(D64 x, D64 y, D64 z, D64 a);
		SIMD256(
			I32 a, I32 b, I32 c, I32 d,
			I32 e, I32 f, I32 g, I32 h);
		SIMD256(const SIMD256& other);
		SIMD256(__m256 other) : myDataF(other) {}
		SIMD256(__m256d other) : myDataD(other) {}
		SIMD256(__m256i other) : myDataI(other) {}
		SIMD256(const Vector3D& other);
		SIMD256(const Vector4D& other);
		~SIMD256() {}

		operator __m256() { return myDataF; }
		operator __m256d() { return myDataD; }
		operator __m256i() { return myDataI; }

		Vector3D toVec3D();
		Vector4D toVec4D();

		void load(const F32* address) override;
		void load(const D64* address) override;
		void loadAlign(const F32* address) override;
		void loadAlign(const D64* address) override;

		void store(F32* address) override;
		void store(D64* address) override;
		void storeAlign(F32* address) override;
		void storeAlign(D64* address) override;

	private:
		union
		{
			__m256 myDataF;
			__m256d myDataD;
			__m256i myDataI;
		};
	};
}

#endif // !_DYNAMIK_SIMD_256_H
