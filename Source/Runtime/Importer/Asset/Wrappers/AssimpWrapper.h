// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ASSIMP_WRAPPER_H
#define _DYNAMIK_ASSIMP_WRAPPER_H

#include "Core/Components/RenderableComponents/StaticMeshComponent.h"
#include "Animation/AnimatedMeshComponent.h"

namespace Dynamik
{
	/*
	 Assimp Wrapper for the Dynamik Engine
	 This class contains wrappers to import and export asset files using the Assimp library.
	*/
	class DMK_API AssimpWrapper {
	public:
		AssimpWrapper() {}
		~AssimpWrapper() {}

		/*
		 Load mesh component using an aiMesh object.

		 @param pAiMeshObject: Pointer to the aiMesh object.
		 @param vertexLayout: Vertex layout of the Dynamik Mesh Component.
		*/
		DMKStaticMeshComponent loadMeshComponent(VPTR pAiMeshObject, const DMKVertexLayout& vertexLayout);

		/*
		 Load animation using aiAnimation and the root node.

		 @param pAiAnimation: pointer to the animation.
		 @param pAiRootNode: Root node of the aiScene object.
		*/
		DMKAnimation loadAnimation(VPTR pAiAnimation, VPTR pAiRootNode);

		/*
		 Load an animated mesh component using aiScene object.

		 @param pAiSceneObject: Pointer to the aiScene object.
		 @param vertexLayout: Vertex layout of the mesh component.
		*/
		DMKAnimatedMeshComponent loadAnimatedMeshComponent(VPTR pAiSceneObject, const DMKVertexLayout& vertexLayout, const UI32& nodesPerVertex = 4);

		/*
		 Load animated meshes from an asset file.

		 @param file: Asset file.
		 @param vertexLayout: Vertex layout of the skinned mesh.
		*/
		DMKAnimatedMeshComponent loadAnimatedModel(const STRING& file, const DMKVertexLayout& vertexLayout, const UI32& nodesPerVertex = 4);

		/*
		 Load a static model using Assimp.

		 @param file: Asset file.
		 @param vertexLayout: Vertex layout of the vertex buffers used to store vertex data.
		*/
		ARRAY<DMKStaticMeshComponent> loadStaticModel(const STRING& file, const DMKVertexLayout& vertexLayout);
	};
}

#endif // !_DYNAMIK_ASSIMP_WRAPPER_H