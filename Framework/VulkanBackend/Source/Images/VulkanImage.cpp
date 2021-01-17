// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Images/VulkanImage.h"

namespace DMK
{
	namespace VulkanBackend
	{
		namespace _Helpers
		{
			VkFormat GetFormat(Format format)
			{
				switch (format)
				{
				case DMK::Format::RG_4_UNORMAL_PACK8:
					return VK_FORMAT_R4G4_UNORM_PACK8;

				case DMK::Format::RGBA_4_UNORMAL_PACK16:
					return VK_FORMAT_R4G4B4A4_UNORM_PACK16;

				case DMK::Format::BGRA_4_UNORMAL_PACK16:
					return VK_FORMAT_B4G4R4A4_UNORM_PACK16;

				case DMK::Format::R5G6B5_UNORMAL_PACK16:
					return VK_FORMAT_R5G6B5_UNORM_PACK16;

				case DMK::Format::B5G6R5_UNORMAL_PACK16:
					return VK_FORMAT_B5G6R5_UNORM_PACK16;

				case DMK::Format::R5G6B5A1_UNORMAL_PACK16:
					return VK_FORMAT_B5G6R5_UNORM_PACK16;

				case DMK::Format::B5G6R5A1_UNORMAL_PACK16:
					return VK_FORMAT_B5G5R5A1_UNORM_PACK16;

				case DMK::Format::A1B5G6R5_UNORMAL_PACK16:
					return VK_FORMAT_A1R5G5B5_UNORM_PACK16;

				case DMK::Format::R_8_UNORMAL:

				case DMK::Format::R_8_SNORMAL:

				case DMK::Format::R_8_USCALED:

				case DMK::Format::R_8_SSCALED:

				case DMK::Format::R_8_UINT:

				case DMK::Format::R_8_SINT:

				case DMK::Format::R_8_SRGB:

				case DMK::Format::RG_8_UNORMAL:

				case DMK::Format::RG_8_SNORMAL:

				case DMK::Format::RG_8_USCALED:

				case DMK::Format::RG_8_SSCALED:

				case DMK::Format::RG_8_UINT:

				case DMK::Format::RG_8_SINT:

				case DMK::Format::RG_8_SRGB:

				case DMK::Format::RGB_8_UNORMAL:

				case DMK::Format::RGB_8_SNORMAL:

				case DMK::Format::RGB_8_USCALED:

				case DMK::Format::RGB_8_SSCALED:

				case DMK::Format::RGB_8_UINT:

				case DMK::Format::RGB_8_SINT:

				case DMK::Format::RGB_8_SRGB:

				case DMK::Format::BGR_8_UNORMAL:

				case DMK::Format::BGR_8_SNORMAL:

				case DMK::Format::BGR_8_USCALED:

				case DMK::Format::BGR_8_SSCALED:

				case DMK::Format::BGR_8_UINT:

				case DMK::Format::BGR_8_SINT:

				case DMK::Format::BGR_8_SRGB:

				case DMK::Format::RGBA_8_UNORMAL:

				case DMK::Format::RGBA_8_SNORMAL:

				case DMK::Format::RGBA_8_USCALED:

				case DMK::Format::RGBA_8_SSCALED:

				case DMK::Format::RGBA_8_UINT:

				case DMK::Format::RGBA_8_SINT:

				case DMK::Format::RGBA_8_SRGB:

				case DMK::Format::BGRA_8_UNORMAL:

				case DMK::Format::BGRA_8_SNORMAL:

				case DMK::Format::BGRA_8_USCALED:

				case DMK::Format::BGRA_8_SSCALED:

				case DMK::Format::BGRA_8_UINT:

				case DMK::Format::BGRA_8_SINT:

				case DMK::Format::BGRA_8_SRGB:

				case DMK::Format::RGBA_8_UNORMAL_PACK32:

				case DMK::Format::RGBA_8_SNORMAL_PACK32:

				case DMK::Format::RGBA_8_USCALED_PACK32:

				case DMK::Format::RGBA_8_SSCALED_PACK32:

				case DMK::Format::RGBA_8_UINT_PACK32:

				case DMK::Format::RGBA_8_SINT_PACK32:

				case DMK::Format::RGBA_8_SRGB_PACK32:

				case DMK::Format::A2R10G10B10_UNORMAL_PACK32:

				case DMK::Format::A2R10G10B10_SNORMAL_PACK32:

				case DMK::Format::A2R10G10B10_USCALED_PACK32:

				case DMK::Format::A2R10G10B10_SSCALED_PACK32:

				case DMK::Format::A2R10G10B10_UINT_PACK32:

				case DMK::Format::A2R10G10B10_SINT_PACK32:

				case DMK::Format::A2B10G10R10_UNORMAL_PACK32:

				case DMK::Format::A2B10G10R10_SNORMAL_PACK32:

				case DMK::Format::A2B10G10R10_USCALED_PACK32:

				case DMK::Format::A2B10G10R10_SSCALED_PACK32:

				case DMK::Format::A2B10G10R10_UINT_PACK32:

				case DMK::Format::A2B10G10R10_SINT_PACK32:

				case DMK::Format::R_16_UNORMAL:

				case DMK::Format::R_16_SNORMAL:

				case DMK::Format::R_16_USCALED:

				case DMK::Format::R_16_SSCALED:

				case DMK::Format::R_16_UINT:

				case DMK::Format::R_16_SINT:

				case DMK::Format::R_16_SFLOAT:

				case DMK::Format::RG_16_UNORMAL:

				case DMK::Format::RG_16_SNORMAL:

				case DMK::Format::RG_16_USCALED:

				case DMK::Format::RG_16_SSCALED:

				case DMK::Format::RG_16_UINT:

				case DMK::Format::RG_16_SINT:

				case DMK::Format::RG_16_SFLOAT:

				case DMK::Format::RGB_16_UNORMAL:

				case DMK::Format::RGB_16_SNORMAL:

				case DMK::Format::RGB_16_USCALED:

				case DMK::Format::RGB_16_SSCALED:

				case DMK::Format::RGB_16_UINT:

				case DMK::Format::RGB_16_SINT:

				case DMK::Format::RGB_16_SFLOAT:

				case DMK::Format::RGBA_16_UNORMAL:

				case DMK::Format::RGBA_16_SNORMAL:

				case DMK::Format::RGBA_16_USCALED:

				case DMK::Format::RGBA_16_SSCALED:

				case DMK::Format::RGBA_16_UINT:

				case DMK::Format::RGBA_16_SINT:

				case DMK::Format::RGBA_16_SFLOAT:

				case DMK::Format::R_32_UINT:

				case DMK::Format::R_32_SINT:

				case DMK::Format::R_32_SFLOAT:

				case DMK::Format::RG_32_UINT:

				case DMK::Format::RG_32_SINT:

				case DMK::Format::RG_32_SFLOAT:

				case DMK::Format::RGB_32_UINT:

				case DMK::Format::RGB_32_SINT:

				case DMK::Format::RGB_32_SFLOAT:

				case DMK::Format::RGBA_32_UINT:

				case DMK::Format::RGBA_32_SINT:

				case DMK::Format::RGBA_32_SFLOAT:

				case DMK::Format::R_64_UINT:

				case DMK::Format::R_64_SINT:

				case DMK::Format::R_64_SFLOAT:

				case DMK::Format::RG_64_UINT:

				case DMK::Format::RG_64_SINT:

				case DMK::Format::RG_64_SFLOAT:

				case DMK::Format::RGB_64_UINT:

				case DMK::Format::RGB_64_SINT:

				case DMK::Format::RGB_64_SFLOAT:

				case DMK::Format::RGBA_64_UINT:

				case DMK::Format::RGBA_64_SINT:

				case DMK::Format::RGBA_64_SFLOAT:

				case DMK::Format::B10G11R11_UFLOAT_PACK32:

				case DMK::Format::E5B9G9R9_UFLOAT_PACK32:

				case DMK::Format::D_16_UNORM:

				case DMK::Format::X8_D_24_UNORM_PACK32:

				case DMK::Format::D_32_SFLOAT:

				case DMK::Format::S_8_UINT:

				case DMK::Format::D_16_UNORM_S_8_UINT:

				case DMK::Format::D_24_UNORM_S_8_UINT:

				case DMK::Format::D_32_SFLOAT_S_8_UINT:

				case DMK::Format::BC1_RGB_UNORM_BLOCK:

				case DMK::Format::BC1_RGB_SRGB_BLOCK:

				case DMK::Format::BC1_RGBA_UNORM_BLOCK:

				case DMK::Format::BC1_RGBA_SRGB_BLOCK:

				case DMK::Format::BC2_UNORM_BLOCK:

				case DMK::Format::BC2_SRGB_BLOCK:

				case DMK::Format::BC3_UNORM_BLOCK:

				case DMK::Format::BC3_SRGB_BLOCK:

				case DMK::Format::BC4_UNORM_BLOCK:

				case DMK::Format::BC4_SNORM_BLOCK:

				case DMK::Format::BC5_UNORM_BLOCK:

				case DMK::Format::BC5_SNORM_BLOCK:

				case DMK::Format::BC6H_UFLOAT_BLOCK:

				case DMK::Format::BC6H_SFLOAT_BLOCK:

				case DMK::Format::BC7_UNORM_BLOCK:

				case DMK::Format::BC7_SRGB_BLOCK:

				case DMK::Format::ETC2_RGB_8_UNORM_BLOCK:

				case DMK::Format::ETC2_RGB_8_SRGB_BLOCK:

				case DMK::Format::ETC2_R8G8B8A1_UNORM_BLOCK:

				case DMK::Format::ETC2_R8G8B8A1_SRGB_BLOCK:

				case DMK::Format::ETC2_RGBA_8_UNORM_BLOCK:

				case DMK::Format::ETC2_RGBA_8_SRGB_BLOCK:

				case DMK::Format::EAC_R_11_UNORM_BLOCK:

				case DMK::Format::EAC_R_11_SNORM_BLOCK:

				case DMK::Format::EAC_RG_11_UNORM_BLOCK:

				case DMK::Format::EAC_RG_11_SNORM_BLOCK:

				case DMK::Format::ASTC_4x4_UNORM_BLOCK:

				case DMK::Format::ASTC_4x4_SRGB_BLOCK:

				case DMK::Format::ASTC_5x4_UNORM_BLOCK:

				case DMK::Format::ASTC_5x4_SRGB_BLOCK:

				case DMK::Format::ASTC_5x5_UNORM_BLOCK:

				case DMK::Format::ASTC_5x5_SRGB_BLOCK:

				case DMK::Format::ASTC_6x5_UNORM_BLOCK:

				case DMK::Format::ASTC_6x5_SRGB_BLOCK:

				case DMK::Format::ASTC_6x6_UNORM_BLOCK:

				case DMK::Format::ASTC_6x6_SRGB_BLOCK:

				case DMK::Format::ASTC_8x5_UNORM_BLOCK:

				case DMK::Format::ASTC_8x5_SRGB_BLOCK:

				case DMK::Format::ASTC_8x6_UNORM_BLOCK:

				case DMK::Format::ASTC_8x6_SRGB_BLOCK:

				case DMK::Format::ASTC_8x8_UNORM_BLOCK:

				case DMK::Format::ASTC_8x8_SRGB_BLOCK:

				case DMK::Format::ASTC_10x5_UNORM_BLOCK:

				case DMK::Format::ASTC_10x5_SRGB_BLOCK:

				case DMK::Format::ASTC_10x6_UNORM_BLOCK:

				case DMK::Format::ASTC_10x6_SRGB_BLOCK:

				case DMK::Format::ASTC_10x8_UNORM_BLOCK:

				case DMK::Format::ASTC_10x8_SRGB_BLOCK:

				case DMK::Format::ASTC_10x10_UNORM_BLOCK:

				case DMK::Format::ASTC_10x10_SRGB_BLOCK:

				case DMK::Format::ASTC_12x10_UNORM_BLOCK:

				case DMK::Format::ASTC_12x10_SRGB_BLOCK:

				case DMK::Format::ASTC_12x12_UNORM_BLOCK:

				case DMK::Format::ASTC_12x12_SRGB_BLOCK:
					break;
				}

				return VkFormat::VK_FORMAT_UNDEFINED;
			}
		}

		void CreateImage(VkDevice vLogicalDevice, VkSampleCountFlags sampleCount, VkImageUsageFlags imageUsage)
		{
			//VkImageCreateInfo vCI = {};
			//vCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			//vCI.pNext = VK_NULL_HANDLE;
			//vCI.extent = { static_cast<UI32>(mExtent.x), static_cast<UI32>(mExtent.y), static_cast<UI32>(mExtent.z) };
			//vCI.initialLayout = vCurrentLayout;
			//vCI.queueFamilyIndexCount = 0;
			//vCI.pQueueFamilyIndices = VK_NULL_HANDLE;
			//vCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			//vCI.tiling = VK_IMAGE_TILING_LINEAR;
			//vCI.mipLevels = mMipLevels;
		}

		void CreateImageMemory(VkDevice vLogicalDevice, VkPhysicalDevice vPhysicalDevice)
		{
		}
	}
}