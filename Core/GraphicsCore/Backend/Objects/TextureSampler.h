// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_TEXTURE_SAMPLER_H
#define _DYNAMIK_GRAPHICS_CORE_TEXTURE_SAMPLER_H

#include "Texture.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Texture Sampler for the Dynamik Engine.
		 * This object is used to render a texture.
		 */
		class TextureSampler : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			TextureSampler() {}

			/**
			 * Default destructor.
			 */
			virtual ~TextureSampler() {}
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_TEXTURE_SAMPLER_H
