// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Objects/ShaderCode.h"
#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanDevice;

		/**
		 * Vulkan Shader Module object.
		 */
		class ShaderModule {
		public:
			/**
			 * Default constructor.
			 */
			ShaderModule() {}

			/**
			 * Default destructor.
			 */
			~ShaderModule() {}

			/**
			 * Initialize the shader module.
			 * This method also uses the reflection data to generate descriptors.
			 *
			 * @param shaderCode: The shader code object.
			 */
			void Initialize(const VulkanDevice& vDevice, const GraphicsCore::ShaderCode& shaderCode);

			/**
			 * Terminate the shader module.
			 */
			void Terminate(const VulkanDevice& vDevice);

			std::vector<VkDescriptorSetLayoutBinding> vLayoutBindings;	// Descriptor set layout bindings.
			std::vector<VkVertexInputAttributeDescription> vInputAttributes;	// Vertex input attributes.
			std::vector<VkVertexInputBindingDescription> vInputBindings;	// Vertex input bindings.
			std::vector<VkDescriptorPoolSize> vDescriptorPoolSizes;	// Descriptor pool sizes.
			std::vector<VkPushConstantRange> vPushConstantRanges;	// Push constant ranges.
			VkShaderModule vShaderModule = VK_NULL_HANDLE;	// Vulkan shader module.
		};
	}
}