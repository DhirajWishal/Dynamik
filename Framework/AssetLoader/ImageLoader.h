// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Materials/Texture.h"

namespace DMK
{
	namespace AssetLoader
	{
		/**
		 * Load image data from a file.
		 *
		 * @param pAsset: The asset path.
		 * @return The texture material.
		 */
		GraphicsCore::Texture LoadImageData(const char* pAsset);
	}
}