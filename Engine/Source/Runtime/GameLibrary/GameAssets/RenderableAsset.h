#pragma once
#ifndef _DYNAMIK_RENDERABLE_ASSET_H
#define _DYNAMIK_RENDERABLE_ASSET_H

/*
 Author:	Dhiraj Wishal
 Date:		04/06/2020
*/
#include "../GameAsset.h"
#include "Events/EventHandler.h"

namespace Dynamik
{
	/*
	 Dynamik Renderable Asset
	*/
	class DMK_API DMKRenderableAsset : public DMKGameAsset {
	public:
		DMKRenderableAsset() {}
		virtual ~DMKRenderableAsset() {}

	public:		/* Virtual functions */
		virtual void initialize() override;

		virtual void onUpdate(const DMKEventBuffer& eventBuffer);

	protected:	/* Utility functions */
		/*
		 Create a new mesh component and add it to the mesh store. Return the address of the last element 
		 of the store.
		 If the specified path contain more than one mesh, all of it will be loaded and added to the store.
		*/
		POINTER<DMKMeshComponent> createMeshComponent(STRING path, ARRAY<DMKUniformDescription> uniformDescriptors);
		
		/*
		 Create a new mesh component and add it to the mesh store. Return the address of the last element
		 of the store.
		*/
		POINTER<DMKMeshComponent> createMeshComponent(ARRAY<DMKVertexObject> vertexData, ARRAY<UI32> indexData, DMKVertexBufferDescriptor vertexDescription, ARRAY<DMKUniformDescription> uniformDescriptors);

		/*
		 Create a basic camera uniform buffer object (Model, View, Projection)
		*/
		DMKUniformDescription createUniformMVP();

	public:		/* Variables */
		/*
		 Locations on which the object is rendered. This way we dont have to have multiple copies of the same
		 model/ mesh.
		*/
		ARRAY<VEC3F> locations;

		/*
		 Mesh data store
		*/
		ARRAY<DMKMeshComponent> meshComponents;

		/* Material description of the game object */
		POINTER<DMKMaterialDescriptor> materialDescription;
	};
}

#endif // !_DYNAMIK_RENDERABLE_ASSET_H
