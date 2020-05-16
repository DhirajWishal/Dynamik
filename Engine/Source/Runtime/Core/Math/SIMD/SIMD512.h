#pragma once
#ifndef _DYNAMIK_SIMD_512_H
#define _DYNAMIK_SIMD_512_H

/*
 Author:    Dhiraj Wishal
 Date:      16/05/2020
*/
#include "Base.h"

namespace Dynamik
{
    /*
     Container class to contain a 512 bit (16 floats) SIMD data packet.
    */
    DMK_ALIGN class DMK_API SIMD512 : public BaseSIMD {
    public:
        SIMD512();
        SIMD512(F32 value);
        SIMD512(I32 value);
        SIMD512(F32 x, F32 y);
        SIMD512(const SIMD512& other);
        //SIMD128(__m128 other) : myData(other) {}
        //SIMD128(const Vector3D& other);
        ~SIMD512() {}

    private:
        __m512 myData;
    };
}

#endif // !_DYNAMIK_SIMD_64_H
