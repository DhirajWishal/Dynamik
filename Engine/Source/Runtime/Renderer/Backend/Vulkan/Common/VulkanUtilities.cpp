#include "dmkafx.h"
#include "VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		VkFormat VulkanUtilities::getVulkanFormat(DMKFormat format)
		{
			switch (format)
			{
			case Dynamik::DMKFormat::DMK_FORMAT_UNDEFINED:			return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_R_8_UINT:			return VkFormat::VK_FORMAT_R8_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_R_8_SINT:			return VkFormat::VK_FORMAT_R8_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_R_8_SNORMAL:		return VkFormat::VK_FORMAT_R8_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_R_8_SSCALED:		return VkFormat::VK_FORMAT_R8_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_R_8_USCALED:		return VkFormat::VK_FORMAT_R8_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_R_8_SRGB:			return VkFormat::VK_FORMAT_R8_SRGB;
			case Dynamik::DMKFormat::DMK_FORMAT_R_8_UNORMAL:		return VkFormat::VK_FORMAT_R8_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_R_16_UINT:			return VkFormat::VK_FORMAT_R16_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_R_16_SINT:			return VkFormat::VK_FORMAT_R16_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_R_16_SNORMAL:		return VkFormat::VK_FORMAT_R16_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_R_16_SSCALED:		return VkFormat::VK_FORMAT_R16_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_R_16_USCALED:		return VkFormat::VK_FORMAT_R16_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_R_16_SRGB:			return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_R_16_UNORMAL:		return VkFormat::VK_FORMAT_R16_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_R_32_UINT:			return VkFormat::VK_FORMAT_R32_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_R_32_SINT:			return VkFormat::VK_FORMAT_R32_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_R_32_SNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_R_32_SSCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_R_32_USCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_R_32_SRGB:			return VkFormat::VK_FORMAT_R32_SFLOAT;
			case Dynamik::DMKFormat::DMK_FORMAT_R_32_UNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_8_UINT:			return VkFormat::VK_FORMAT_R8G8_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_8_SINT:			return VkFormat::VK_FORMAT_R8G8_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_8_SNORMAL:		return VkFormat::VK_FORMAT_R8G8_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_8_SSCALED:		return VkFormat::VK_FORMAT_R8G8_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_8_USCALED:		return VkFormat::VK_FORMAT_R8G8_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_8_SRGB:			return VkFormat::VK_FORMAT_R8G8_SRGB;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_8_UNORMAL:		return VkFormat::VK_FORMAT_R8G8_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_16_UINT:			return VkFormat::VK_FORMAT_R16G16_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_16_SINT:			return VkFormat::VK_FORMAT_R16G16_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_16_SNORMAL:		return VkFormat::VK_FORMAT_R16G16_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_16_SSCALED:		return VkFormat::VK_FORMAT_R16G16_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_16_USCALED:		return VkFormat::VK_FORMAT_R16G16_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_16_SRGB:			return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_16_UNORMAL:		return VkFormat::VK_FORMAT_R16G16_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_32_UINT:			return VkFormat::VK_FORMAT_R32G32_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_32_SINT:			return VkFormat::VK_FORMAT_R32G32_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_32_SNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_32_SSCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_32_USCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_32_SRGB:			return VkFormat::VK_FORMAT_R32G32_SFLOAT;
			case Dynamik::DMKFormat::DMK_FORMAT_RG_32_UNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_UINT:			return VkFormat::VK_FORMAT_R8G8B8_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SINT:			return VkFormat::VK_FORMAT_R8G8B8_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SNORMAL:		return VkFormat::VK_FORMAT_R8G8B8_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SSCALED:		return VkFormat::VK_FORMAT_R8G8B8_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_USCALED:		return VkFormat::VK_FORMAT_R8G8B8_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_SRGB:			return VkFormat::VK_FORMAT_R8G8B8_SRGB;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_8_UNORMAL:		return VkFormat::VK_FORMAT_R8G8B8_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_UINT:		return VkFormat::VK_FORMAT_R16G16B16_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SINT:		return VkFormat::VK_FORMAT_R16G16B16_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SNORMAL:		return VkFormat::VK_FORMAT_R16G16B16_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SSCALED:		return VkFormat::VK_FORMAT_R16G16B16_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_USCALED:		return VkFormat::VK_FORMAT_R16G16B16_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_SRGB:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_16_UNORMAL:		return VkFormat::VK_FORMAT_R16G16B16_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_UINT:		return VkFormat::VK_FORMAT_R32G32B32_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_SINT:		return VkFormat::VK_FORMAT_R32G32B32_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_SNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_SSCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_USCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_SRGB:		return VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGB_32_UNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_UINT:			return VkFormat::VK_FORMAT_B8G8R8_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SINT:			return VkFormat::VK_FORMAT_B8G8R8_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SNORMAL:		return VkFormat::VK_FORMAT_B8G8R8_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SSCALED:		return VkFormat::VK_FORMAT_B8G8R8_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_USCALED:		return VkFormat::VK_FORMAT_B8G8R8_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_SRGB:			return VkFormat::VK_FORMAT_B8G8R8_SRGB;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_8_UNORMAL:		return VkFormat::VK_FORMAT_B8G8R8_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_16_UINT:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_16_SINT:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_16_SNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_16_SSCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_16_USCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_16_SRGB:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_16_UNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_32_UINT:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_32_SINT:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_32_SNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_32_SSCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_32_USCALED:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_32_SRGB:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGR_32_UNORMAL:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UINT:		return VkFormat::VK_FORMAT_R8G8B8A8_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SINT:		return VkFormat::VK_FORMAT_R8G8B8A8_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SNORMAL:		return VkFormat::VK_FORMAT_R8G8B8A8_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SSCALED:		return VkFormat::VK_FORMAT_R8G8B8A8_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_USCALED:		return VkFormat::VK_FORMAT_R8G8B8A8_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_SRGB:		return VkFormat::VK_FORMAT_R8G8B8A8_SRGB;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_8_UNORMAL:		return VkFormat::VK_FORMAT_R8G8B8A8_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_UINT:		return VkFormat::VK_FORMAT_R16G16B16A16_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SINT:		return VkFormat::VK_FORMAT_R16G16B16A16_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SNORMAL:	return VkFormat::VK_FORMAT_R16G16B16A16_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SSCALED:	return VkFormat::VK_FORMAT_R16G16B16A16_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_USCALED:	return VkFormat::VK_FORMAT_R16G16B16A16_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_SRGB:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_16_UNORMAL:	return VkFormat::VK_FORMAT_R16G16B16A16_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_UINT:		return VkFormat::VK_FORMAT_R32G32B32A32_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_SINT:		return VkFormat::VK_FORMAT_R32G32B32A32_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_SNORMAL:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_SSCALED:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_USCALED:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_SRGB:		return VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT;
			case Dynamik::DMKFormat::DMK_FORMAT_RGBA_32_UNORMAL:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_UINT:		return VkFormat::VK_FORMAT_B8G8R8A8_UINT;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SINT:		return VkFormat::VK_FORMAT_B8G8R8A8_SINT;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SNORMAL:		return VkFormat::VK_FORMAT_B8G8R8A8_SNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SSCALED:		return VkFormat::VK_FORMAT_B8G8R8A8_SSCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_USCALED:		return VkFormat::VK_FORMAT_B8G8R8A8_USCALED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_SRGB:		return VkFormat::VK_FORMAT_B8G8R8A8_SRGB;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_8_UNORMAL:		return VkFormat::VK_FORMAT_B8G8R8A8_UNORM;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_16_UINT:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_16_SINT:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_16_SNORMAL:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_16_SSCALED:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_16_USCALED:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_16_SRGB:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_16_UNORMAL:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_32_UINT:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_32_SINT:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_32_SNORMAL:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_32_SSCALED:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_32_USCALED:	return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_32_SRGB:		return VkFormat::VK_FORMAT_UNDEFINED;
			case Dynamik::DMKFormat::DMK_FORMAT_BGRA_32_UNORMAL:	return VkFormat::VK_FORMAT_UNDEFINED;
			}

			return VkFormat::VK_FORMAT_UNDEFINED;
		}

		UI32 VulkanUtilities::findMemoryType(UI32 typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice)
		{
			VkPhysicalDeviceMemoryProperties memProperties;
			vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

			for (UI32 i = 0; i < memProperties.memoryTypeCount; i++)
				if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags
					& properties) == properties)
					return i;

			DMK_ERROR_BOX("Failed to find suitable memory type!");
			return 0;
		}
	}
}