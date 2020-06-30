// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_TYPES_H
#define _DYNAMIK_MATH_TYPES_H

/*
 This file contains all the math types of the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "Vector/Vector2F.h"
#include "Vector/Vector3F.h"
#include "Vector/Vector4F.h"

#include "Matrix/Matrix2F.h"
#include "Matrix/Matrix3F.h"
#include "Matrix/Matrix4F.h"

namespace Dynamik
{
    typedef Vector2F VEC2;
    typedef Vector3F VEC3;
    typedef Vector4F VEC4;

    typedef Matrix2F MAT2;
    typedef Matrix3F MAT3;
    typedef Matrix4F MAT4;
}

#endif // !_DYNAMIK_MATH_TYPES_H
