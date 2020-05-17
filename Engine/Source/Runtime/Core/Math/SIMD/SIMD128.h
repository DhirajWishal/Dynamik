#pragma once
#ifndef _DYNAMIK_SIMD_128_H
#define _DYNAMIK_SIMD_128_H

/*
 Author:    Dhiraj Wishal
 Date:      16/05/2020
*/
#include "Base.h"
#include "Vector3F.h"
#include "Vector4F.h"

namespace Dynamik
{
	/*
	 Container class to contain a 128 bit (4 floats) SIMD data packet.
	*/
	class DMK_API SIMD128 : public BaseSIMD {
	public:
		SIMD128();
		SIMD128(F32 value);
		SIMD128(D64 value);
		SIMD128(I32 value);
		SIMD128(F32 x, F32 y, F32 z, F32 a);
		SIMD128(D64 x, D64 y);
		SIMD128(I32 x, I32 y, I32 z, I32 a);
		SIMD128(const SIMD128& other);
		SIMD128(__m128 other) : myDataF(other) {}
		SIMD128(__m128d other) : myDataD(other) {}
		SIMD128(__m128i other) : myDataI(other) {}
		SIMD128(const Vector3F& other);
		SIMD128(const Vector4F& other);
		~SIMD128() {}

		operator __m128() const { return myDataF; }
		operator __m128d() const { return myDataD; }
		operator __m128i() const { return myDataI; }

		Vector3F toVec3F();
		//Vector3D toVec3D();
		Vector4F toVec4F();
		//Vector4D toVec4D();

		void load(const F32* address) override;
		void load(const D64* address) override;
		void load(const I32* address) override;
		void loadAlign(const F32* address) override;
		void loadAlign(const D64* address) override;

		void store(F32* address) override;
		void store(D64* address) override;
		void store(I32* address) override;
		void storeAlign(F32* address) override;
		void storeAlign(D64* address) override;

	private:
		union
		{
			__m128 myDataF;
			__m128d myDataD;
			__m128i myDataI;
		};
	};
}

#endif // !_DYNAMIK_SIMD_128_H
