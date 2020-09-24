// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_ACCELERATION_STRUCTURE_H
#define _DYNAMIK_VULKAN_ACCELERATION_STRUCTURE_H

#include "Renderer/Components/Primitives/RAccelerationStructure.h"
#include "../VulkanCoreObject.h"

namespace Backend
{
	/*
	 Vulkan Acceleration Structure 
	*/
	class DMK_API VulkanAccelerationStructure : public RAccelerationStructure {
	public:
		VulkanAccelerationStructure() {}
		~VulkanAccelerationStructure() {}

		virtual void createBottomLevelStructure(RCoreObject* pCoreObject, RBuffer* pVertexBuffer, UI64 vertexCount, UI64 vertexSize, RBuffer* pIndexBuffer, UI64 indexCount) override final;
		virtual void createTopLevelStructure(RCoreObject* pCoreObject, RAccelerationStructure* pBottomLevelStructure) override final;
		virtual void terminate(RCoreObject* pCoreObject) override final;

		UI64 getDeviceAddress() const;

		VkBuffer getBuffer() const;
		VkDeviceMemory getBufferMemory() const;
		VkDeviceMemory getObjectMemory() const;
		operator VkAccelerationStructureKHR() const;

		UI64 deviceAddress = 0;

		VkBuffer buffer = VK_NULL_HANDLE;
		VkDeviceMemory bufferMemory = VK_NULL_HANDLE;
		VkDeviceMemory objectMemory = VK_NULL_HANDLE;
		VkAccelerationStructureKHR accelerationStructure = VK_NULL_HANDLE;

	private:
		void createScratchBuffer(RCoreObject* pCoreObject);
		void terminateScratchBuffer(RCoreObject* pCoreObject);
		void createObjectMemory(RCoreObject* pCoreObject);

		UI64 getBufferDeviceAddress(RCoreObject* pCoreObject, const VkBuffer& vBuffer);
	};
}

#endif // !_DYNAMIK_VULKAN_ACCELERATION_STRUCTURE_H
