// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_BUFFER_FACTORY_H
#define _DYNAMIK_BUFFER_FACTORY_H

#include "../Primitives/RBuffer.h"

/*
 Dynamik Buffer Factory
*/
class DMK_API DMKBufferFactory {
public:
	DMKBufferFactory() {}
	~DMKBufferFactory() {}

	void setDefaults(DMKRenderingAPI api, RCoreObject* pCoreObject);

	RBuffer* createVertexBuffer(UI64 uSize,
		RResourceMemoryType memoryType = (RResourceMemoryType)
		(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
	RBuffer* createIndexBuffer(UI64 uSize,
		RResourceMemoryType memoryType = (RResourceMemoryType)
		(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
	RBuffer* createUniformBuffer(UI64 uSize,
		RResourceMemoryType memoryType = (RResourceMemoryType)
		(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
	RBuffer* createStaggingBuffer(UI64 uSize,
		RResourceMemoryType memoryType = (RResourceMemoryType)
		(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));

private:
	DMKRenderingAPI myRenderingAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;
	RCoreObject* myCoreObject;
};

#endif // !_DYNAMIK_BUFFER_FACTORY_H
