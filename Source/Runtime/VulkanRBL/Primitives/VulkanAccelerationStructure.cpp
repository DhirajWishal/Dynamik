// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanAccelerationStructure.h"

#include "../VulkanUtilities.h"
#include "../Common/VulkanOneTimeCommandBuffer.h"

namespace Backend
{
	void VulkanAccelerationStructure::createBottomLevelStructure(RCoreObject* pCoreObject, RBuffer* pVertexBuffer, UI64 vertexCount, UI64 vertexSize, RBuffer* pIndexBuffer, UI64 indexCount)
	{
		VkDeviceOrHostAddressConstKHR vertexBufferDeviceAddress = {};
		VkDeviceOrHostAddressConstKHR indexBufferDeviceAddress = {};

		const uint32_t triangleCount = Cast<UI32>(indexCount) / 3;

		vertexBufferDeviceAddress.deviceAddress = getBufferDeviceAddress(pCoreObject, Inherit<VulkanBuffer>(pVertexBuffer)->buffer);
		indexBufferDeviceAddress.deviceAddress = getBufferDeviceAddress(pCoreObject, Inherit<VulkanBuffer>(pIndexBuffer)->buffer);

		VkAccelerationStructureCreateGeometryTypeInfoKHR accelerationCreateGeometryInfo = {};
		accelerationCreateGeometryInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_GEOMETRY_TYPE_INFO_KHR;
		accelerationCreateGeometryInfo.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;
		accelerationCreateGeometryInfo.maxPrimitiveCount = triangleCount;
		accelerationCreateGeometryInfo.indexType = VK_INDEX_TYPE_UINT32;
		accelerationCreateGeometryInfo.maxVertexCount = Cast<UI32>(vertexCount);
		accelerationCreateGeometryInfo.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
		accelerationCreateGeometryInfo.allowsTransforms = VK_FALSE;

		VkAccelerationStructureCreateInfoKHR accelerationCI = {};
		accelerationCI.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
		accelerationCI.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
		accelerationCI.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
		accelerationCI.maxGeometryCount = 1;
		accelerationCI.pGeometryInfos = &accelerationCreateGeometryInfo;

		DMK_VULKAN_ASSERT(vkCreateAccelerationStructureKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, &accelerationCI, nullptr, &accelerationStructure), "Failed to create acceleration structure!");

		/* Create the object memory. */
		createObjectMemory(pCoreObject);

		VkBindAccelerationStructureMemoryInfoKHR bindAccelerationMemoryInfo = {};
		bindAccelerationMemoryInfo.sType = VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_KHR;
		bindAccelerationMemoryInfo.accelerationStructure = accelerationStructure;
		bindAccelerationMemoryInfo.memory = objectMemory;

		DMK_VULKAN_ASSERT(vkBindAccelerationStructureMemoryKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, 1, &bindAccelerationMemoryInfo), "Failed to bind acceleration structure memory!");

		VkAccelerationStructureGeometryKHR accelerationStructureGeometry = {};
		accelerationStructureGeometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
		accelerationStructureGeometry.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;
		accelerationStructureGeometry.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;
		accelerationStructureGeometry.geometry.triangles.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
		accelerationStructureGeometry.geometry.triangles.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
		accelerationStructureGeometry.geometry.triangles.vertexData.deviceAddress = vertexBufferDeviceAddress.deviceAddress;
		accelerationStructureGeometry.geometry.triangles.vertexStride = vertexSize;
		accelerationStructureGeometry.geometry.triangles.indexType = VK_INDEX_TYPE_UINT32;
		accelerationStructureGeometry.geometry.triangles.indexData.deviceAddress = indexBufferDeviceAddress.deviceAddress;

		ARRAY<VkAccelerationStructureGeometryKHR> acceleration_geometries = { accelerationStructureGeometry };
		VkAccelerationStructureGeometryKHR* acceleration_structure_geometries = acceleration_geometries.data();

		/* Create scratch buffer. */
		createScratchBuffer(pCoreObject);

		VkAccelerationStructureBuildGeometryInfoKHR accelerationBuildGeometryInfo{};
		accelerationBuildGeometryInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
		accelerationBuildGeometryInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
		accelerationBuildGeometryInfo.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
		accelerationBuildGeometryInfo.update = VK_FALSE;
		accelerationBuildGeometryInfo.dstAccelerationStructure = accelerationStructure;
		accelerationBuildGeometryInfo.geometryArrayOfPointers = VK_FALSE;
		accelerationBuildGeometryInfo.geometryCount = 1;
		accelerationBuildGeometryInfo.ppGeometries = &acceleration_structure_geometries;
		accelerationBuildGeometryInfo.scratchData.deviceAddress = deviceAddress;

		VkAccelerationStructureBuildOffsetInfoKHR accelerationBuildOffsetInfo{};
		accelerationBuildOffsetInfo.primitiveCount = triangleCount;
		accelerationBuildOffsetInfo.primitiveOffset = 0x0;
		accelerationBuildOffsetInfo.firstVertex = 0;
		accelerationBuildOffsetInfo.transformOffset = 0x0;

		ARRAY<VkAccelerationStructureBuildOffsetInfoKHR*> accelerationBuildOffsets = { &accelerationBuildOffsetInfo };

		if (Inherit<VulkanCoreObject>(pCoreObject)->device.getRayTracingFeatures().rayTracingHostAccelerationStructureCommands)
		{
			// Implementation supports building acceleration structure building on host
			DMK_VULKAN_ASSERT(vkBuildAccelerationStructureKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, 1, &accelerationBuildGeometryInfo, accelerationBuildOffsets.data()), "Failed to build acceleration structure!");
		}
		else
		{
			// Acceleration structure needs to be build on the device
			VulkanOneTimeCommandBuffer _buffer(pCoreObject);
			vkCmdBuildAccelerationStructureKHR(_buffer, 1, &accelerationBuildGeometryInfo, accelerationBuildOffsets.data());
		}

		VkAccelerationStructureDeviceAddressInfoKHR accelerationDeviceAddressInfo{};
		accelerationDeviceAddressInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
		accelerationDeviceAddressInfo.accelerationStructure = accelerationStructure;
	
		handle = vkGetAccelerationStructureDeviceAddressKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, &accelerationDeviceAddressInfo);
	
		terminateScratchBuffer(pCoreObject);
	}

	void VulkanAccelerationStructure::createTopLevelStructure(RCoreObject* pCoreObject, RAccelerationStructure* pBottomLevelStructure)
	{
		VkAccelerationStructureCreateGeometryTypeInfoKHR accelerationCreateGeometryInfo = {};
		accelerationCreateGeometryInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_GEOMETRY_TYPE_INFO_KHR;
		accelerationCreateGeometryInfo.geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
		accelerationCreateGeometryInfo.maxPrimitiveCount = 1;
		accelerationCreateGeometryInfo.allowsTransforms = VK_FALSE;

		VkAccelerationStructureCreateInfoKHR accelerationCI = {};
		accelerationCI.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
		accelerationCI.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
		accelerationCI.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
		accelerationCI.maxGeometryCount = 1;
		accelerationCI.pGeometryInfos = &accelerationCreateGeometryInfo;

		DMK_VULKAN_ASSERT(vkCreateAccelerationStructureKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, &accelerationCI, nullptr, &accelerationStructure), "Failed to create acceleration structure!");

		/* Create object memory. */
		createObjectMemory(pCoreObject);

		VkBindAccelerationStructureMemoryInfoKHR bindAccelerationMemoryInfo{};
		bindAccelerationMemoryInfo.sType = VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_KHR;
		bindAccelerationMemoryInfo.accelerationStructure = accelerationStructure;
		bindAccelerationMemoryInfo.memory = objectMemory;

		DMK_VULKAN_ASSERT(vkBindAccelerationStructureMemoryKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, 1, &bindAccelerationMemoryInfo), "Failed to bind acceleration structure memory!");

		VkTransformMatrixKHR transform_matrix = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f };

		VkAccelerationStructureInstanceKHR instance{};
		instance.transform = transform_matrix;
		instance.instanceCustomIndex = 0;
		instance.mask = 0xFF;
		instance.instanceShaderBindingTableRecordOffset = 0;
		instance.flags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR;
		instance.accelerationStructureReference = pBottomLevelStructure->getHandle();

		/* Instance data buffer */
		VulkanBuffer instanceDataBuffer = {};
		instanceDataBuffer.initialize(pCoreObject, RBufferType::BUFFER_TYPE_SHADER_DEVICE, sizeof(instance), RResourceMemoryType(RResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RResourceMemoryType::RESOURCE_MEMORY_TYPE_HOST_COHERENT));
		instanceDataBuffer.setData(pCoreObject, sizeof(instance), 0, &instance);

		VkDeviceOrHostAddressConstKHR instance_data_device_address{};
		instance_data_device_address.deviceAddress = getBufferDeviceAddress(pCoreObject, instanceDataBuffer.buffer);
	
		VkAccelerationStructureGeometryKHR accelerationStructureGeometry{};
		accelerationStructureGeometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
		accelerationStructureGeometry.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;
		accelerationStructureGeometry.geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
		accelerationStructureGeometry.geometry.instances.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
		accelerationStructureGeometry.geometry.instances.arrayOfPointers = VK_FALSE;
		accelerationStructureGeometry.geometry.instances.data.deviceAddress = instance_data_device_address.deviceAddress;

		ARRAY<VkAccelerationStructureGeometryKHR> acceleration_geometries = { accelerationStructureGeometry };
		VkAccelerationStructureGeometryKHR* acceleration_structure_geometries = acceleration_geometries.data();

		createScratchBuffer(pCoreObject);

		VkAccelerationStructureBuildGeometryInfoKHR accelerationBuildGeometryInfo{};
		accelerationBuildGeometryInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
		accelerationBuildGeometryInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
		accelerationBuildGeometryInfo.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
		accelerationBuildGeometryInfo.update = VK_FALSE;
		accelerationBuildGeometryInfo.srcAccelerationStructure = VK_NULL_HANDLE;
		accelerationBuildGeometryInfo.dstAccelerationStructure = accelerationStructure;
		accelerationBuildGeometryInfo.geometryArrayOfPointers = VK_FALSE;
		accelerationBuildGeometryInfo.geometryCount = 1;
		accelerationBuildGeometryInfo.ppGeometries = &acceleration_structure_geometries;
		accelerationBuildGeometryInfo.scratchData.deviceAddress = deviceAddress;

		VkAccelerationStructureBuildOffsetInfoKHR accelerationBuildOffsetInfo{};
		accelerationBuildOffsetInfo.primitiveCount = 1;
		accelerationBuildOffsetInfo.primitiveOffset = 0x0;
		accelerationBuildOffsetInfo.firstVertex = 0;
		accelerationBuildOffsetInfo.transformOffset = 0x0;
		ARRAY<VkAccelerationStructureBuildOffsetInfoKHR*> accelerationBuildOffsets = { &accelerationBuildOffsetInfo };
	
		if (Inherit<VulkanCoreObject>(pCoreObject)->device.getRayTracingFeatures().rayTracingHostAccelerationStructureCommands)
		{
			// Implementation supports building acceleration structure building on host
			DMK_VULKAN_ASSERT(vkBuildAccelerationStructureKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, 1, &accelerationBuildGeometryInfo, accelerationBuildOffsets.data()), "Failed to build the acceleration structure!");
		}
		else
		{
			// Acceleration structure needs to be build on the device
			VulkanOneTimeCommandBuffer _buffer(pCoreObject);
			vkCmdBuildAccelerationStructureKHR(_buffer, 1, &accelerationBuildGeometryInfo, accelerationBuildOffsets.data());
		}

		VkAccelerationStructureDeviceAddressInfoKHR accelerationDeviceAddressInfo{};
		accelerationDeviceAddressInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
		accelerationDeviceAddressInfo.accelerationStructure = accelerationStructure;

		handle = vkGetAccelerationStructureDeviceAddressKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, &accelerationDeviceAddressInfo);
	
		instanceDataBuffer.terminate(pCoreObject);
		terminateScratchBuffer(pCoreObject);
	}

	void VulkanAccelerationStructure::terminate(RCoreObject* pCoreObject)
	{
		vkDestroyBuffer(Inherit<VulkanCoreObject>(pCoreObject)->device, buffer, nullptr);
		vkFreeMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, bufferMemory, nullptr);
		vkFreeMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, objectMemory, nullptr);
	}

	UI64 VulkanAccelerationStructure::getDeviceAddress() const
	{
		return this->deviceAddress;
	}

	VulkanAccelerationStructure::operator VkAccelerationStructureKHR() const
	{
		return this->accelerationStructure;
	}

	void VulkanAccelerationStructure::createScratchBuffer(RCoreObject* pCoreObject)
	{
		VkAccelerationStructureMemoryRequirementsInfoKHR accelerationStructureMemoryRequirements = {};
		accelerationStructureMemoryRequirements.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_KHR;
		accelerationStructureMemoryRequirements.type = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_KHR;
		accelerationStructureMemoryRequirements.buildType = VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR;
		accelerationStructureMemoryRequirements.accelerationStructure = accelerationStructure;

		VkMemoryRequirements2 memoryRequirements2 = {};
		memoryRequirements2.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
		vkGetAccelerationStructureMemoryRequirementsKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, &accelerationStructureMemoryRequirements, &memoryRequirements2);

		VkBufferCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		createInfo.size = memoryRequirements2.memoryRequirements.size;
		createInfo.usage = VK_BUFFER_USAGE_RAY_TRACING_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
		createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		DMK_VULKAN_ASSERT(vkCreateBuffer(Inherit<VulkanCoreObject>(pCoreObject)->device, &createInfo, nullptr, &buffer), "Failed to create buffer!");

		VkMemoryRequirements memRequirements = {};
		vkGetBufferMemoryRequirements(Inherit<VulkanCoreObject>(pCoreObject)->device, buffer, &memRequirements);

		VkMemoryAllocateFlagsInfo memoryAllocateFlags{};
		memoryAllocateFlags.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
		memoryAllocateFlags.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.pNext = &memoryAllocateFlags;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = VulkanUtilities::findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, Inherit<VulkanCoreObject>(pCoreObject)->device);

		DMK_VULKAN_ASSERT(vkAllocateMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, &allocInfo, nullptr, &bufferMemory), "Failed to allocate buffer memory!");

		vkBindBufferMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, buffer, bufferMemory, 0);

		VkBufferDeviceAddressInfoKHR bufferDeviceAddressInfo{};
		bufferDeviceAddressInfo.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
		bufferDeviceAddressInfo.buffer = buffer;
		deviceAddress = vkGetBufferDeviceAddressKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, &bufferDeviceAddressInfo);
	}

	void VulkanAccelerationStructure::terminateScratchBuffer(RCoreObject* pCoreObject)
	{
		vkDestroyBuffer(Inherit<VulkanCoreObject>(pCoreObject)->device, buffer, nullptr);
		vkFreeMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, bufferMemory, nullptr);
	}

	void VulkanAccelerationStructure::createObjectMemory(RCoreObject* pCoreObject)
	{
		VkAccelerationStructureMemoryRequirementsInfoKHR accelerationStructureMemoryRequirements = {};
		accelerationStructureMemoryRequirements.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_KHR;
		accelerationStructureMemoryRequirements.type = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_KHR;
		accelerationStructureMemoryRequirements.buildType = VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR;
		accelerationStructureMemoryRequirements.accelerationStructure = accelerationStructure;

		VkMemoryRequirements2 memoryRequirements2 = {};
		memoryRequirements2.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
		vkGetAccelerationStructureMemoryRequirementsKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, &accelerationStructureMemoryRequirements, &memoryRequirements2);

		VkMemoryRequirements memoryRequirements = memoryRequirements2.memoryRequirements;

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memoryRequirements.size;
		allocInfo.memoryTypeIndex = VulkanUtilities::findMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, Inherit<VulkanCoreObject>(pCoreObject)->device);

		DMK_VULKAN_ASSERT(vkAllocateMemory(Inherit<VulkanCoreObject>(pCoreObject)->device, &allocInfo, nullptr, &objectMemory), "Failed to allocate object memory!");
	}

	UI64 VulkanAccelerationStructure::getBufferDeviceAddress(RCoreObject* pCoreObject, const VkBuffer& vBuffer)
	{
		VkBufferDeviceAddressInfoKHR bufferDeviceAI = {};
		bufferDeviceAI.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
		bufferDeviceAI.buffer = vBuffer;
		return vkGetBufferDeviceAddressKHR(Inherit<VulkanCoreObject>(pCoreObject)->device, &bufferDeviceAI);
	}

	VkBuffer VulkanAccelerationStructure::getBuffer() const
	{
		return this->buffer;
	}

	VkDeviceMemory VulkanAccelerationStructure::getBufferMemory() const
	{
		return this->bufferMemory;
	}

	VkDeviceMemory VulkanAccelerationStructure::getObjectMemory() const
	{
		return this->objectMemory;
	}
}
