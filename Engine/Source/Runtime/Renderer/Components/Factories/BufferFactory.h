// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_BUFFER_FACTORY_H
#define _DYNAMIK_BUFFER_FACTORY_H

/*
 Author:	Dhiraj Wishal
 Date:		17/06/2020
*/
#include "../Primitives/RBuffer.h"

namespace Dynamik
{
	/*
	 Dynamik Buffer Factory
	*/
	class DMK_API DMKBufferFactory {
	public:
		DMKBufferFactory() {}
		~DMKBufferFactory() {}

		void setDefaults(DMKRenderingAPI api, POINTER<RCoreObject> pCoreObject);

		POINTER<RBuffer> createVertexBuffer(UI64 uSize,
			RResourceMemoryType memoryType = (RResourceMemoryType)
			(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
		POINTER<RBuffer> createIndexBuffer(UI64 uSize,
			RResourceMemoryType memoryType = (RResourceMemoryType)
			(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
		POINTER<RBuffer> createUniformBuffer(UI64 uSize,
			RResourceMemoryType memoryType = (RResourceMemoryType)
			(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));
		POINTER<RBuffer> createStaggingBuffer(UI64 uSize,
			RResourceMemoryType memoryType = (RResourceMemoryType)
			(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT));

	private:
		DMKRenderingAPI myRenderingAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;
		POINTER<RCoreObject> myCoreObject;
	};
}

#endif // !_DYNAMIK_BUFFER_FACTORY_H
