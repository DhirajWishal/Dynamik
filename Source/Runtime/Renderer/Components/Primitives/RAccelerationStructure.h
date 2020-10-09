// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_ACCELERATION_STRUCTURE_H
#define _DYNAMIK_RENDERER_ACCELERATION_STRUCTURE_H

#include "RBuffer.h"

/*
 Renderer Acceleration Structure 
 This structure is used to store top level information for ray tracing. 
*/
class DMK_API RAccelerationStructure {
public:
	RAccelerationStructure() {}
	virtual ~RAccelerationStructure() {}

	virtual void createBottomLevelStructure(RCoreObject* pCoreObject, RBuffer* pVertexBuffer, UI64 vertexCount, UI64 vertexSize, RBuffer* pIndexBuffer, UI64 indexCount) = 0;
	virtual void createTopLevelStructure(RCoreObject* pCoreObject, RAccelerationStructure* pBottomLevelStructure) = 0;
	virtual void terminate(RCoreObject* pCoreObject) = 0;

	UI64 getHandle() const { return this->handle; }
	UI64 handle = 0;
};

#endif // !_DYNAMIK_RENDERER_ACCELERATION_STRUCTURE_H
