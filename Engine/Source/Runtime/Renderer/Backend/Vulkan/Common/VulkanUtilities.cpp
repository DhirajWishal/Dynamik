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

		B1 VulkanUtilities::hasStencilComponent(const VkFormat& format)
		{
			return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
		}

		VkFormat VulkanUtilities::findSupportedFormat(const ARRAY<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice)
		{
			for (VkFormat format : candidates) {
				VkFormatProperties props;

				vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

				if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
					return format;

				else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
					return format;
			}

			DMK_ERROR_BOX("Failed to find supported format!");
			return VkFormat();
		}

		VkFormat VulkanUtilities::findDepthFormat(const VkPhysicalDevice& physicalDevice)
		{
			return findSupportedFormat(
				{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
				VK_IMAGE_TILING_OPTIMAL,
				VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,
				physicalDevice
			);
		}

		VkDescriptorType VulkanUtilities::getDescriptorType(DMKUniformType type)
		{
			switch (type)
			{
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER:			return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_BUFFER:			return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER_DYNAMIC:	return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_BUFFER_DYNAMIC:	return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_TEXEL_BUFFER:	return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_TEXEL_BUFFER:	return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_INPUT_ATTACHMENT:		return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_STORAGE_IMAGE:			return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_2D:				return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_CUBE:			return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_2D_ARRAY:		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_SAMPLER_CUBE_ARRAY:		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			case Dynamik::DMKUniformType::DMK_UNIFORM_TYPE_ACCELERATION_STRUCTURE:	return VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;
			default:
				DMK_ERROR_BOX("Invalid uniform type!");
				break;
			}

			return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		}

		VkShaderStageFlagBits VulkanUtilities::getShaderStage(DMKShaderLocation location)
		{
			switch (location)
			{
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX:		return VK_SHADER_STAGE_VERTEX_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_TESSELLATION:	return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_GEOMETRY:		return VK_SHADER_STAGE_GEOMETRY_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT:		return VK_SHADER_STAGE_FRAGMENT_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_COMPUTE:		return VK_SHADER_STAGE_COMPUTE_BIT;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_ALL_GRAPHICS:	return VK_SHADER_STAGE_ALL;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_RAY_GEN:		return VK_SHADER_STAGE_RAYGEN_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_ANY_HIT:		return VK_SHADER_STAGE_ANY_HIT_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_CLOSEST_HIT:	return VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_MISS:			return VK_SHADER_STAGE_MISS_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_INTERSECTION:	return VK_SHADER_STAGE_INTERSECTION_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_CALLABLE:		return VK_SHADER_STAGE_CALLABLE_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_TASK:			return VK_SHADER_STAGE_TASK_BIT_NV;
			case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_MESH:			return VK_SHADER_STAGE_MESH_BIT_NV;
			default:
				DMK_ERROR_BOX("Invalid shader location!");
				break;
			}

			return VK_SHADER_STAGE_ALL;
		}

		ARRAY<VkDescriptorSetLayoutBinding> VulkanUtilities::getDescriptorSetLayoutBindings(ARRAY<DMKUniformBufferDescriptor> descriptors)
		{
			ARRAY<VkDescriptorSetLayoutBinding> _bindings;

			for (auto _descriptor : descriptors)
			{
				for (auto _object : _descriptor.uniformBufferObjects)
				{
					if (_object.type == DMKUniformType::DMK_UNIFORM_TYPE_CONSTANT)
						continue;

					VkDescriptorSetLayoutBinding _binding;
					_binding.binding = _object.destinationBinding;
					_binding.descriptorCount = 1;
					_binding.descriptorType = getDescriptorType(_object.type);
					_binding.pImmutableSamplers = VK_NULL_HANDLE;
					_binding.stageFlags = getShaderStage(_object.shaderLocation);
					_bindings.pushBack(_binding);
				}
			}

			return _bindings;
		}
	}
}