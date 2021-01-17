// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Material.h"
#include "Core/Maths/Vector/Vector3.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Texture Material object.
		 */
		class Texture final : public Material {
		public:
			Texture() {}
			~Texture() {}

			Vector3 mExtent = Vector3::ZeroAll;
			unsigned char* pImageData = nullptr;
			UI32 mChannels = 0;
		};
	}
}