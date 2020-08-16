// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ENVIRONMENT_MAP_H
#define _DYNAMIK_ENVIRONMENT_MAP_H

#include "Renderer/Entities/StaticModelEntity.h"

namespace Dynamik
{
	/*
	 Dynamik Environment Map
	 This contains all the necessary details of the game environment.

	 Users are allowed to load multiple sky box objects at a time and will be cycled either by using a 
	 user defined method or will use the internal clock to cycle 
	 (allocated time slot per sky box = clock cycle time / total number of sky boxes).
	*/
	class DMK_API DMKEnvironmentMap {
	public:
		DMKEnvironmentMap() = default;
		virtual ~DMKEnvironmentMap() = default;

		/*
		 Add a shader module.

		 @param sModule: The shader module.
		*/
		void addShaderModule(const DMKShaderModule& sModule);

		/*
		 Set the shader modules.

		 @param sModules: The shader modules to be set.
		*/
		void setShaderModules(ARRAY<DMKShaderModule> sModules);

		/*
		 Get a shader module stored in this object.

		 @param index: The index of the shader module.
		*/
		DMKShaderModule* getShaderModule(I32 index);

		/*
		 Get all the shaders stored in the object.
		*/
		ARRAY<DMKShaderModule> getShaders();

		/* The shader modules */
		ARRAY<DMKShaderModule> shaders;

		/* The sky box mesh */
		DMKMeshObject skyBoxMesh;
	};
}

#endif // !_DYNAMIK_ENVIRONMENT_MAP_H
