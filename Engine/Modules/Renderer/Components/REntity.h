// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_ENTITY_H
#define _DYNAMIK_RENDERER_ENTITY_H

#include "RMeshObject.h"

/*
 Renderer Entity 
*/
class DMK_API REntity {
public:
	REntity() = default;
	virtual ~REntity() = default;

	ARRAY<RMeshObject> meshObjects;
	ARRAY<RUniformContainer> uniformContainers;
	VPTR pipelineCache = nullptr;

	/* TODO */
	RPipelineObject* pPipelineObject = nullptr;
	RBuffer* pVertexBuffer = nullptr;
	RBuffer* pIndexBuffer = nullptr;
};

#endif // !_DYNAMIK_RENDERER_ENTITY_H
