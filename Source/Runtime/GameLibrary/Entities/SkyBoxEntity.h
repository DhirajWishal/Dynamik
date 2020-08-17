// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_SKY_BOX_ENTITY_H
#define _DYNAMIK_SKY_BOX_ENTITY_H

#include "Core/Objects/Resources/MeshObject.h"

namespace Dynamik
{
	/*
	 Dynamik Sky Box Entity
	 This entity holds information about a single sky box.
	*/
	class DMK_API DMKSkyBoxEntity {
	public:
		DMKSkyBoxEntity() {}
		virtual ~DMKSkyBoxEntity() {}

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

		/* The shader modules. */
		ARRAY<DMKShaderModule> shaders;

	public:
		/*
		 Set the mesh object data. 
		 Since the sky box is only allowed to have one 
		*/
		void setMeshObject(const DMKMeshObject& meshData);

		/*
		 Get the stored mesh object. 
		*/
		DMKMeshObject* getMeshObject() const;

		/* The mesh of the sky box. */
		DMKMeshObject meshObject;
	};
}

#endif // !_DYNAMIK_SKY_BOX_ENTITY_H
