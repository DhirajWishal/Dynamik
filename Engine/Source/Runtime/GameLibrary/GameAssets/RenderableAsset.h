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

	public:		/* Public Utility Functions */
		/*
		 Add a mesh to the mesh component store.
		*/
		void addToMeshStore(const DMKMeshComponent& component);

		/*
		 Add multiple mesh components to the mesh component store.
		*/
		void addToMeshStore(const ARRAY<DMKMeshComponent>& components);

		/*
		 Get the stored mesh components.
		*/
		ARRAY<DMKMeshComponent> getMeshStore();

	protected:		/* Variables */
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
