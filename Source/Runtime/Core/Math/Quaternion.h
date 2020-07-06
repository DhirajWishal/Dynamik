// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_QUATERNION_H
#define _DYNAMIK_MATH_QUATERNION_H

#include "Vector/Vector4F.h"

namespace Dynamik
{
	/*
	 Quaternion type for the Dynamik Engine
	*/
	class DMK_API Quaternion {
	public:
		Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		~Quaternion() {}

		Vector4F toVector4F() const;

		struct { F32 x, y, z, w; };
	};
}

#endif // !_DYNAMIK_QUATERNION_H
