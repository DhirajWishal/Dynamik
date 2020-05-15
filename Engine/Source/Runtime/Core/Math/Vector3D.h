#pragma once
#ifndef _DYNAMIK_MATH_VECTOR_3D_H
#define _DYNAMIK_MATH_VECTOR_3D_H

/*
 3D Vector for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "Object/Utility.h"

namespace Dynamik
{
    /*
     Basic 3D Vector for the Dynamik Engine.
     This class uses SIMD to carry out the necessary calculations.
    */
    DMK_ALIGN class DMK_API Vector3D : public DMKUtility {
    public:
        Vector3D() {}
        Vector3D(F32 value) {}
        Vector3D(F32 value1, F32 value2, F32 value3) {}
        ~Vector3D() {}

        F32 x = 0.0f;
        F32 y = 0.0f;
        F32 z = 0.0f;
        F32 a = 0.0f;
    };
}

#endif // !_DYNAMIK_MATH_VECTOR_3_H
