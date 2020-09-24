// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "RImageSampler.h"

	RImageSamplerCreateInfo RImageSamplerCreateInfo::createDefaultSampler(F32 levelOfDetail)
	{
		RImageSamplerCreateInfo sampler;
		sampler.minLOD = levelOfDetail;
		return sampler;
	}

	RImageSamplerCreateInfo RImageSamplerCreateInfo::createCubeMapSampler(F32 levelOfDetail)
	{
		RImageSamplerCreateInfo sampler;
		sampler.addressModeU = RImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_REPEAT;
		sampler.addressModeV = RImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_REPEAT;
		sampler.addressModeW = RImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_REPEAT;
		sampler.minLOD = levelOfDetail;

		return sampler;
	}
