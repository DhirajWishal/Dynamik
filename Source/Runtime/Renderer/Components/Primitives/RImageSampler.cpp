#include "dmkafx.h"
#include "RImageSampler.h"

namespace Dynamik
{
	RImageSamplerCreateInfo RImageSamplerCreateInfo::createDefaultSampler()
	{
		return RImageSamplerCreateInfo();
	}

	RImageSamplerCreateInfo RImageSamplerCreateInfo::createCubeMapSampler()
	{
		RImageSamplerCreateInfo sampler;
		sampler.addressModeU = RImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_REPEAT;
		sampler.addressModeV = RImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_REPEAT;
		sampler.addressModeW = RImageSamplerAddressMode::IMAGE_SAMPLER_ADDRESS_MODE_REPEAT;

		return sampler;
	}
}
