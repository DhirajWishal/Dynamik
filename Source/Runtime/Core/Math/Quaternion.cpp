// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Quaternion.h"

namespace Dynamik
{
	Vector4F Quaternion::toVector4F() const
	{
		return Vector4F(x, y, z, w);
	}
}
