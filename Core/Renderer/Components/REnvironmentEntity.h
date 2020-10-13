// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_ENVIRONMENT_ENTITY_H
#define _DYNAMIK_RENDERER_ENVIRONMENT_ENTITY_H

#include "RCoreObject.h"
#include "REntity.h"
#include "Lighting/RBRDFTable.h"
#include "Lighting/RPreFilteredCube.h"
#include "Lighting/RIrradianceCube.h"
#include "GameLibrary/Entities/EnvironmentEntity.h"

class DMK_API DMKEnvironmentEntity;

/*
 Renderer Environment Map
 This object contains all the necessary information needed to render the environment map provided by
 the client application.
*/
class DMK_API REnvironmentEntity {
public:
	REnvironmentEntity() = default;
	virtual ~REnvironmentEntity() = default;

public:		/* Render data */
	REntity renderEntity = {};

public:		/* Resource Data */
	RTexture* pTexture = nullptr;
	std::vector<RUniformContainer> uniformBuffers;

	RBRDFTable* pBRDFTable = nullptr;
	RPreFilteredCube* pPreFilteredCube = nullptr;
	RIrradianceCube* pIrradianceCube = nullptr;

public:		/* Parent Mesh Component*/
	DMKEnvironmentEntity* pParentEntity = nullptr;
};

#endif // !_DYNAMIK_RENDERER_ENVIRONMENT_MAP_H
