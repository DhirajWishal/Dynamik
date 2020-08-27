// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CANVAS_ENTITY_H
#define _DYNAMIK_CANVAS_ENTITY_H

#include "Core/Objects/Resources/MeshObject.h"

namespace Dynamik
{
	/*
	 Dynamik Canvas Entity 
	 Canvas is a 2D entity which the user can draw anything to. 
	*/
	class DMK_API DMKCanvasEntity {
	public:
		DMKCanvasEntity() {}
		virtual~ DMKCanvasEntity() {}

		/*
		 On initialize canvas method. 
		 This method is called by the renderer. 
		*/
		virtual void onInitializeCanvas() {}

		/*
		 On draw canvas method. 
		 This method is called by the renderer. 
		*/
		virtual void onDrawCanvas() {}

		/*
		 On terminate canvas method. 
		 This method is called by the renderer. 
		*/
		virtual void onTerminateCanvas() {}

	public:
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
		 Set the frame mesh object. 

		 @param meshObject: The mesh object to be set as the frame mesh.
		*/
		void setFrameMesh(const DMKMeshObject& meshObject);

		/*
		 Get the current mesh object. 
		*/
		DMKMeshObject* getFrameMesh() const;

		/* The mesh object containing the frame mesh data. */
		DMKMeshObject frameMesh = {};
	};
}

#endif // !_DYNAMIK_CANVAS_ENTITY_H
