#pragma once
#ifndef _DYNAMIK_SIMD_128_H
#define _DYNAMIK_SIMD_128_H

/*
 Author:    Dhiraj Wishal
 Date:      16/05/2020
*/
#include "Base.h"
#include "Vector3D.h"

namespace Dynamik
{
	/*
	 Container class to contain a 128 bit (4 floats) SIMD data packet.
	*/
	DMK_ALIGN class DMK_API SIMD128 : public BaseSIMD {
	public:
		SIMD128();
		SIMD128(F32 value);
		SIMD128(I32 value);
		SIMD128(F32 x, F32 y, F32 z, F32 a);
		SIMD128(const SIMD128& other);
		SIMD128(__m128 other) : myData(other) {}
		SIMD128(const Vector3D& other);
		~SIMD128() {}

		operator __m128() const { return myData; }

		Vector3D toVec3();

		void load(const F32* address) override;
		void loadAlign(const F32* address) override;

		void store(F32* address) override;
		void storeAlign(F32* address) override;

	private:
		__m128 myData;
	};
}

#endif // !_DYNAMIK_SIMD_128_H
