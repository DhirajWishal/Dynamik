// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPLEX_TYPES_H
#define _DYNAMIK_COMPLEX_TYPES_H

/*
 This file contains all the complex types used by the engine.
*/
#include "../Math/Vector/Vector2F.h"
#include "../Math/Vector/Vector4F.h"

namespace Dynamik
{
	/* Dynamik Color Component */
	typedef Vector4F DMKColorComponent;

	/* Dynamik Extent 2D */
	typedef Vector2F DMKExtent2D;

	/* Dynamik Extent 3D */
	typedef Vector3F DMKExtent3D;
}

#endif // !_DYNAMIK_COMPLEX_TYPES_H
