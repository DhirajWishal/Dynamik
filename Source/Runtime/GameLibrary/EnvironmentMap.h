// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ENVIRONMENT_MAP_H
#define _DYNAMIK_ENVIRONMENT_MAP_H

#include "GameEntity.h"

namespace Dynamik
{
	/*
	 Dynamik Environment Map
	 This contains all the necessary details of the game environment.

	 Users are allowed to load multiple sky box objects at a time and will be cycled either by using a 
	 user defined method or will use the internal clock to cycle 
	 (allocated time slot per sky box = clock cycle time / total number of sky boxes).
	*/
	class DMK_API DMKEnvironmentMap : public DMKGameEntity {
	public:
		DMKEnvironmentMap() = default;
		virtual ~DMKEnvironmentMap() = default;

		/*
		 Set the sky box. 
		 The sky box is a static mesh component containing its data. 

		 @param component: The static mesh component.
		*/
		void setSkyBox(const DMKStaticMeshComponent& component);

		/*
		 Set shader modules to the environment map. 

		 @param shaderModules: The shader modules.
		*/
		void setShaders(ARRAY<DMKShaderModule> shaderModules);

		/*
		 Add a shader module to the environment map.

		 @param sModule: The module to be added.
		*/
		void addShaderModule(const DMKShaderModule& sModule);

		DMKStaticMeshComponent skyBox;
		ARRAY<DMKShaderModule> shaderModules;
	};
}

#endif // !_DYNAMIK_ENVIRONMENT_MAP_H
