// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_ENVIRONMENT_MAP_H
#define _DYNAMIK_RENDERER_ENVIRONMENT_MAP_H

#include "RCoreObject.h"
#include "REntity.h"
#include "Lighting/RBRDFTable.h"
#include "Lighting/RPreFilteredCube.h"
#include "Lighting/RIrradianceCube.h"
#include "GameLibrary/EnvironmentMap.h"

namespace Dynamik
{
	class DMK_API DMKEnvironmentMap;

	/*
	 Renderer Environment Map
	 This object contains all the necessary information needed to render the environment map provided by
	 the client application. 
	*/
	class DMK_API REnvironmentMap {
	public:
		REnvironmentMap() = default;
		virtual ~REnvironmentMap() = default;

	public:		/* Vertex and Index Data */
		RBuffer* pVertexBuffer = nullptr;
		RBuffer* pIndexBuffer = nullptr;

		ARRAY<RMeshObject> meshObjects;

	public:		/* Resource Data */
		RTexture* pTexture = nullptr;
		RPipelineObject* pPipeline = nullptr;
		RPipelineResource* pPipelineResource = nullptr;
		ARRAY<RUniformContainer> uniformBuffers;

		RBRDFTable* pBRDFTable = nullptr;
		RPreFilteredCube* pPreFilteredCube = nullptr;
		RIrradianceCube* pIrradianceCube = nullptr;

	public:		/* Parent Mesh Component*/
		DMKEnvironmentMap* pParentEntity = nullptr;
	};
}

#endif // !_DYNAMIK_RENDERER_ENVIRONMENT_MAP_H
