#pragma once
#ifndef _DYNAMIK_SIMD_512_H
#define _DYNAMIK_SIMD_512_H

/*
 Author:    Dhiraj Wishal
 Date:      16/05/2020
*/
#include "Base.h"
#include "../Matrix/Matrix3F.h"
#include "../Matrix/Matrix4F.h"

namespace Dynamik
{
	class DMK_API BaseSIMD;

	/*
	 Container class to contain a 512 bit (16 floats, 8 doubles) SIMD data packet.
	*/
	class DMK_API SIMD512 : public BaseSIMD {
	public:
		SIMD512();
		SIMD512(F32 value);
		SIMD512(D64 value);
		SIMD512(I32 value);
		SIMD512(
			F32 a, F32 b, F32 c, F32 d,
			F32 e, F32 f, F32 g, F32 h,
			F32 i, F32 j, F32 k, F32 l,
			F32 m, F32 n, F32 o, F32 p);
		SIMD512(
			D64 a, D64 b, D64 c, D64 d,
			D64 e, D64 f, D64 g, D64 h);
		SIMD512(
			I32 a, I32 b, I32 c, I32 d,
			I32 e, I32 f, I32 g, I32 h,
			I32 i, I32 j, I32 k, I32 l,
			I32 m, I32 n, I32 o, I32 p);
		SIMD512(const SIMD512& other);
		SIMD512(const __m512& other) : myDataF(other) {}
		SIMD512(const __m512d& other) : myDataD(other) {}
		SIMD512(const __m512i& other) : myDataI(other) {}
		~SIMD512() {}

		operator __m512() { return myDataF; }
		operator __m512d() { return myDataD; }
		operator __m512i() { return myDataI; }

		Matrix4F toMat4F();
		Matrix3F toMat3F();

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
			__m512 myDataF;
			__m512d myDataD;
			__m512i myDataI;
		};
	};
}

#endif // !_DYNAMIK_SIMD_64_H
