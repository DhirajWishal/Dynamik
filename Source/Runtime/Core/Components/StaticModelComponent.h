// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STATIC_MESH_COMPONENT_H
#define _DYNAMIK_STATIC_MESH_COMPONENT_H

#include "Component.h"
#include "Core/Objects/Resources/MeshObject.h"
#include "Core/Types/Utilities.h"

namespace Dynamik
{
	/*
	 Dynamik Mesh Render Specification
	 This describes how a mesh object should be rendered.
	*/
	struct DMK_API DMKRenderSpecification {
		ARRAY<DMKShaderModule> shaders;
	};

	/*
	 Dynamik Static Model Component
	 This model stores all the information of a static model.
	*/
	class DMK_API DMKStaticModelComponent : public DMKComponent {
	public:
		DMKStaticModelComponent() {}
		virtual ~DMKStaticModelComponent() {}

		/*
		 Add a mesh object to the static model. 

		 @param meshObject: The mesh object to be added.
		*/
		void addMeshObject(const DMKMeshObject& meshObject) { meshData.pushBack(meshObject); }

		/*
		 Set the mesh object in the static model.

		 @param meshObjects: The mesh objects to be set.
		*/
		void setMeshObject(ARRAY<DMKMeshObject> meshObjects) { this->meshData = meshObjects; }

		/*
		 Get all the stored mesh objects.
		*/
		DMK_FORCEINLINE ARRAY<DMKMeshObject> getMeshObjects() const { return meshData; }

		/* All the mesh data related to this component */
		ARRAY<DMKMeshObject> meshData;

	public:
		/*
		 Set the render specification of the model.

		 @param specification: The render specification to be set.
		*/
		DMK_FORCEINLINE void setRenderSpecification(const DMKRenderSpecification& specification) { this->renderSpecification = specification; }

		/*
		 Get the render specification of the current model.
		*/
		DMK_FORCEINLINE DMKRenderSpecification& getRenderSpecification() const { return Cast<DMKRenderSpecification&>(renderSpecification); }

		/* The render specification of the model */
		DMKRenderSpecification renderSpecification = {};
	};
}

#endif // !_DYNAMIK_STATIC_MESH_COMPONENT_H
