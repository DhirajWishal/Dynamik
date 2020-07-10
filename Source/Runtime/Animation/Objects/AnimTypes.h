// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_TYPES_H
#define _DYNAMIK_ANIMATION_TYPES_H

/*
 Types used by the animation module.
*/

#include "Core/Math/Quaternion.h"

namespace Dynamik
{
	/* Animation Vector Frame */
	struct DMK_API AVectorFrame {
		AVectorFrame() {}
		AVectorFrame(const Vector3F& vector, const F32& duration) : vector(vector), duration(duration) {}
		AVectorFrame(F32 x, F32 y, F32 z) : vector({ x, y, z }) {}
		~AVectorFrame() {}

		DMK_FORCEINLINE AVectorFrame& operator=(const Vector3F& vector)
		{
			this->vector = vector;
			return *this;
		}

		DMK_FORCEINLINE operator Vector3F() const
		{
			return this->vector;
		}

		Vector3F vector = Vector3F(0.0f);
		F32 duration = 0.0f;
	};

	/* Animation Quaternion Frame */
	struct DMK_API AQuatFrame {
		AQuatFrame() {}
		AQuatFrame(const Quaternion& quat, const F32& duration) : quat(quat), duration(duration) {}
		AQuatFrame(F32 x, F32 y, F32 z, F32 w) : quat({ x, y, z, w }) {}
		~AQuatFrame() {}

		DMK_FORCEINLINE AQuatFrame& operator=(const Quaternion& quat)
		{
			this->quat = quat;
			return *this;
		}

		DMK_FORCEINLINE operator Quaternion() const
		{
			return this->quat;
		}

		Quaternion quat = Quaternion(0.0f);
		F32 duration = 0.0f;
	};
}

#endif // !_DYNAMIK_ANIMATION_TYPES_H