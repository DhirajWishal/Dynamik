// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_IMAGE_SAMPLER_H
#define _DYNAMIK_RENDERER_IMAGE_SAMPLER_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "../RCoreObject.h"

namespace Dynamik
{
	/*
	 Renderer Image Sampler Create Info
	*/
	struct DMK_API RImageSamplerCreateInfo {

	};

	/*
	 Renderer Image Sampler
	*/
	class DMK_API RImageSampler {
	public:
		RImageSampler() {}
		virtual ~RImageSampler() {}

		virtual void initialize(POINTER<RCoreObject> pCoreObject, RImageSamplerCreateInfo createInfo) = 0;
		virtual void terminate(POINTER<RCoreObject> pCoreObject) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_IMAGE_SAMPLER_H
