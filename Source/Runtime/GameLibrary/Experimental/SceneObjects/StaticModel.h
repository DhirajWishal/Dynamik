// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_EXPERIMENTAL_STATIC_MODEL_H
#define _DYNAMIK_EXPERIMENTAL_STATIC_MODEL_H

#include "../SceneObject.h"
#include "Core/Objects/Resources/MeshObject.h"

namespace Dynamik
{
	namespace Experimental
	{
		/*
		 Dynamik Static Model
		 This object contains all the information about a static model.
		*/
		class DMK_API DMKStaticModel : public DMKSceneObject {
		public:
			DMKStaticModel() {}
			~DMKStaticModel() {}

			/*
			 Load a model from an asset file. 
			 
			 @param asset: The asset file path.
			 @param vertexLayout: The vertex layout to load data to. Default is DMKVertexLayout::createBasicIBL().
			 @param indexSize: The size of an index of the index buffer. Default is the size of UI32.
			*/
			void loadModel(const STRING& asset, const DMKVertexLayout& vertexLayout = DMKVertexLayout::createBasicIBL(), UI64 indexSize = sizeof(UI32));

			/*
			 Get the number of meshes stored in the mode. 
			*/
			const UI64 getMeshCount();

			/*
			 Get a mesh from the model. 
			 This method returns the pointer to that object.

			 @param index: The index of the mesh object.
			*/
			DMKMeshObject* getMeshObject(UI64 index);

			/* The mesh objects */
			ARRAY<DMKMeshObject> meshObjects;
		};
	}
}

#endif // !_DYNAMIK_EXPERIMENTAL_STATIC_MODEL_H
