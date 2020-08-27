// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_BUFFER_H
#define _DYNAMIK_RENDERER_BUFFER_H

#include "../RCoreObject.h"
#include "../PrimitiveTypeDefs.h"

/*
 Renderer Buffer
*/
class DMK_API RBuffer {
public:
	RBuffer() {}
	virtual ~RBuffer() {}

	virtual void initialize(RCoreObject* pCoreObject, RBufferType eType, UI64 uSize,
		RResourceMemoryType memoryType = (RResourceMemoryType)
		(RESOURCE_MEMORY_TYPE_HOST_VISIBLE | RESOURCE_MEMORY_TYPE_HOST_COHERENT)) = 0;
	virtual void terminate(RCoreObject* pCoreObject) = 0;

	virtual void copy(RCoreObject* pCoreObject, RBuffer* pSrcBuffer, UI64 size, UI64 srcOffset = 0, UI64 dstOffset = 0) = 0;

	virtual void setData(RCoreObject* pCoreObject, UI64 uSize, UI64 offset, VPTR data) = 0;
	/*
	 Automatically maps memory
	*/
	virtual VPTR getData(RCoreObject* pCoreObject, UI64 uSize, UI64 offset) { return nullptr; }
	virtual void unmapMemory(RCoreObject* pCoreObject) = 0;
	virtual void flushMemory(RCoreObject* pCoreObject) = 0;

	virtual UI64 getSize() { return size; }
	virtual RBufferType getType() { return type; }

protected:
	UI64 size = 0;
	RBufferType type = RBufferType::BUFFER_TYPE_VERTEX;
};

#endif // !_DYNAMIK_RENDERER_BUFFER_H
