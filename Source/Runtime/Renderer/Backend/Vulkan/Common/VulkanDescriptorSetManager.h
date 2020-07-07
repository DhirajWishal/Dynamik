// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_DESCRIPTOR_SET_MANAGER_H
#define _DYNAMIK_VULKAN_DESCRIPTOR_SET_MANAGER_H

#include "VulkanDevice.h"
#include "../Primitives/VulkanBuffer.h"
#include "../Primitives/VulkanTexture.h"
#include "Core/Components/RenderableComponents/MeshComponent.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Descriptor Container
		*/
		struct DMK_API VulkanDescriptorContainer {
			VkDescriptorSetLayout* layoutPtr;
			VkDescriptorPool* poolPtr;
			VkDescriptorSet set = VK_NULL_HANDLE;
		};

		/*
		 Vulkan Descriptor
		 A descriptor is allocated per object/ entity.
		*/
		struct DMK_API VulkanDescriptor {
			VkDescriptorSetLayout layout = VK_NULL_HANDLE;
			VkDescriptorPool pool = VK_NULL_HANDLE;
			VkDescriptorSet set = VK_NULL_HANDLE;
		};

		/*
		 Descriptor create info
		*/
		struct DMK_API VulkanDescriptorInitInfo {
			ARRAY<VulkanTexture> textures;
			ARRAY<VulkanBuffer> uniformBuffers;
		};

		/*
		 Vulkan Descriptor Set manager for the Dynamik RBL
		 Every object contains a uniform ID which is made from its uniform buffer descriptors. This ID is unique
		 for objects containing unique uniform buffer descriptors.
		*/
		class DMK_API VulkanDescriptorSetManager {
		public:
			VulkanDescriptorSetManager() {}
			~VulkanDescriptorSetManager() {}

			VulkanDescriptor createDescriptor(const VulkanDevice& vDevice, ARRAY<ARRAY<VkDescriptorSetLayoutBinding>> layouts, ARRAY<ARRAY<VkDescriptorPoolSize>> poolSizes);
			void terminateDescriptor(const VulkanDevice& vDevice, const VulkanDescriptor& vDescriptor);

			void updateDescriptor(const VulkanDevice& vDevice, const VkDescriptorSet vSet, ARRAY<std::pair<VkDescriptorBufferInfo, UI32>> bufferInfos, ARRAY<VkDescriptorImageInfo> imageInfos, ARRAY<ARRAY<VkDescriptorSetLayoutBinding>> layouts);
		};
	}
}

#endif // !_DYNAMIK_VULKAN_DESCRIPTOR_SET_MANAGER_H
