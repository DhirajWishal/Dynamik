// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_ENVIRONMENT_MAP_H
#define _DYNAMIK_RENDERER_ENVIRONMENT_MAP_H

/*
 Author:	Dhiraj Wishal
 Date:		28/06/2020
*/
#include "RCoreObject.h"
#include "REntity.h"

namespace Dynamik
{
	/*
	 Renderer Environment Map
	 This object contains all the necessary information needed to render the environment map provided by
	 the client application. 
	*/
	class DMK_API REnvironmentMap {
	public:
		REnvironmentMap() = default;
		virtual ~REnvironmentMap() = default;

		/* Stores the sky box object */
		REntity* pSkyBox = nullptr;
	};
}

#endif // !_DYNAMIK_RENDERER_ENVIRONMENT_MAP_H
