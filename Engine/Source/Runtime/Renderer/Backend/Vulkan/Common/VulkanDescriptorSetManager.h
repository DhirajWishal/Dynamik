#pragma once
#ifndef _DYNAMIK_VULKAN_DESCRIPTOR_SET_MANAGER_H
#define _DYNAMIK_VULKAN_DESCRIPTOR_SET_MANAGER_H

/*
 Author:    Dhiraj Wishal
 Date:      30/05/2020
*/
#include "VulkanDevice.h"

#include "Object/Resource/Primitives.h"

namespace Dynamik
{
	namespace Backend
	{
		/*
		 Vulkan Descriptor Set manager for the Dynamik RBL
		 Every object contains a uniform ID which is made from its uniform buffer descriptors. This ID is unique
		 for objects containing unique uniform buffer descriptors.
		*/
		class DMK_API VulkanDescriptorSetManager {

			/*
			 This container contains the basic information of a descriptor set.
			*/
			struct DMK_API VulkanDescriptor {
				operator VkDescriptorSetLayout() const;
				operator VkDescriptorPool() const;
				const VkDescriptorSet operator[](I32 index) const;

				VkDescriptorSet get();

				ARRAY<VkDescriptorSet> sets;
				VkDescriptorSetLayout layout = VK_NULL_HANDLE;
				VkDescriptorPool pool = VK_NULL_HANDLE;

				I64 baseID = 0;
				I64 nextSet = 0;
			};

		public:
			VulkanDescriptorSetManager() {}
			~VulkanDescriptorSetManager() {}

			void createDescriptor(const VulkanDevice& vDevice, const ARRAY<DMKUniformBufferDescriptor>& descriptors, I64 ID, UI32 setCount);

			void terminateDescriptor(const VulkanDevice& vDevice, I64 ID);
			void terminate(const VulkanDevice& vDevice);

		private:
			B1 _isNewAvailable(I64 ID);

			ARRAY<VulkanDescriptor> descriptors;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_DESCRIPTOR_SET_MANAGER_H
