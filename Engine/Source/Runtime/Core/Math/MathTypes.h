#pragma once
#ifndef _DYNAMIK_MATH_TYPES_H
#define _DYNAMIK_MATH_TYPES_H

/*
 This file contains all the math types of the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "Vector/Vector2F.h"
#include "Vector/Vector2D.h"
#include "Vector/Vector3F.h"
#include "Vector/Vector3D.h"
#include "Vector/Vector4F.h"
#include "Vector/Vector4D.h"

#include "Matrix/Matrix2F.h"
#include "Matrix/Matrix3F.h"
#include "Matrix/Matrix4F.h"

namespace Dynamik
{
    typedef Vector2F VEC2F;
    typedef Vector2D VEC2D;
    typedef Vector3F VEC3F;
    typedef Vector3D VEC3D;
    typedef Vector4F VEC4F;
    typedef Vector4D VEC4D;

    typedef Matrix2F MAT2F;
    typedef Matrix3F MAT3F;
    typedef Matrix4F MAT4F;
}

#endif // !_DYNAMIK_MATH_TYPES_H
