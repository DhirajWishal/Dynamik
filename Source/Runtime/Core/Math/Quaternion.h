// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATH_QUATERNION_H
#define _DYNAMIK_MATH_QUATERNION_H

#include "Vector/Vector3F.h"
#include "Vector/Vector4F.h"

namespace Dynamik
{
	/*
	 Quaternion type for the Dynamik Engine
	*/
	class DMK_API Quaternion {
	public:
		Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Quaternion(const F32& value) : x(value), y(value), z(value), w(value) {}
		Quaternion(const F32& x, const F32& y, const F32& z, const F32& w)
			: x(x), y(y), z(z), w(w) {}
		Quaternion(const Vector3F& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
		Quaternion(const Vector4F& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
		~Quaternion() {}

		Quaternion operator=(const Vector4F& other);

		Vector3F toVector3F() const;
		Vector4F toVector4F() const;

		struct { F32 x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f; };
	};
}

#endif // !_DYNAMIK_QUATERNION_H
