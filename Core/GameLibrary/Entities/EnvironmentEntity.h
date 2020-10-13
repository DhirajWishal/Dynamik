// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ENVIRONMENT_ENTITY_H
#define _DYNAMIK_ENVIRONMENT_ENTITY_H

#include "GameLibrary/Entities/StaticModelEntity.h"

/*
 Dynamik Environment Map
 This contains all the necessary details of the game environment.

 Users are allowed to load multiple sky box objects at a time and will be cycled either by using a
 user defined method or will use the internal clock to cycle
 (allocated time slot per sky box = clock cycle time / total number of sky boxes).
*/
class DMK_API DMKEnvironmentEntity {
public:
	DMKEnvironmentEntity() = default;
	virtual ~DMKEnvironmentEntity() = default;

	/*
	 On initialize environment method.
	 This method is called once the entity is submitted to the rendering engine.
	*/
	virtual void onInitializeEnvironment() {}

	/*
	 On update environment method.
	 This method is called by the rendering engine.
	*/
	virtual void onUpdateEnvironment() {}

	/*
	 On terminate environment method.
	*/
	virtual void onTerminateEnvironment() {}

	/*
	 Add a shader module.

	 @param sModule: The shader module.
	*/
	void addShaderModule(const DMKShaderModule& sModule);

	/*
	 Set the shader modules.

	 @param sModules: The shader modules to be set.
	*/
	void setShaderModules(std::vector<DMKShaderModule> sModules);

	/*
	 Get a shader module stored in this object.

	 @param index: The index of the shader module.
	*/
	DMKShaderModule* getShaderModule(I32 index);

	/*
	 Get all the shaders stored in the object.
	*/
	std::vector<DMKShaderModule> getShaders();

	/* The shader modules */
	std::vector<DMKShaderModule> shaders;

	/* The sky box mesh */
	DMKMeshObject skyBoxMesh;

public:
	/*
	 Clear all the data of the environment map. (Only cleans the mesh object).
	*/
	void clearEnvironmentMap();

	bool isInitializedEnvironmentEntity = false;
};

#endif // !_DYNAMIK_ENVIRONMENT_MAP_H