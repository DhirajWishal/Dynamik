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

	std::vector<RMeshObject> meshObjects;
	std::vector<RUniformContainer> uniformContainers;
	void* pipelineCache = nullptr;

	/* TODO */
	RPipelineObject* pPipelineObject = nullptr;
	RBuffer* pVertexBuffer = nullptr;
	RBuffer* pIndexBuffer = nullptr;
};

#endif // !_DYNAMIK_RENDERER_ENTITY_H
