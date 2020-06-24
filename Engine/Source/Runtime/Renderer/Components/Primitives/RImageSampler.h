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
#include "../PrimitiveTypeDefs.h"

namespace Dynamik
{
	/*
	 Renderer Image Sampler Create Info
	*/
	struct DMK_API RImageSamplerCreateInfo {
		RImageSamplerFilter magFilter = RImageSamplerFilter::IMAGE_SAMPLER_FILTER_LINEAR;
		RImageSamplerFilter minFilter = RImageSamplerFilter::IMAGE_SAMPLER_FILTER_LINEAR;
		RImageSamplerAddressMode addressModeU = RImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		RImageSamplerAddressMode addressModeV = RImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		RImageSamplerAddressMode addressModeW = RImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		B1 enableAnisotropy = false;
		F32 maxAntisotropy = 16.0f;
		RImageSamplerBorderColor borderColor = RImageSamplerBorderColor::IMAGE_SAMPLER_BORDER_COLOR_F32_OPAQUE_BLACK;
		B1 unnormalizedCoordinates = false;
		B1 compareEnable = false;
		RStencilCompareOp compareOp = RStencilCompareOp::STENCIL_COMPARE_OP_NEVER;
		RResourceMipMapMode mipmapMode = RResourceMipMapMode::RESOURCE_MIPMAP_MODE_LINEAR;
		F32 minLOD = 0.0f;
		F32 maxLOD = 1.0f;
		F32 mipLODBias = 0.0f;
	};

	/*
	 Renderer Image Sampler
	*/
	class DMK_API RImageSampler {
	public:
		RImageSampler() {}
		virtual ~RImageSampler() {}

		virtual void initialize(RCoreObject* pCoreObject, RImageSamplerCreateInfo createInfo) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_IMAGE_SAMPLER_H
