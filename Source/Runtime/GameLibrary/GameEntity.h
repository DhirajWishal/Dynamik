// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_ENTITY_H
#define _DYNAMIK_GAME_ENTITY_H

/*
 Game Entity for the Dynamik Engine.
*/
#include "ComponentSystem/ComponentManager.h"
#include "Core/Types/ObjectArray.h"
#include "Core/Components/PrimitiveCompoennts.h"

namespace Dynamik
{
	class DMK_API DMKLevelComponent;

	/*
	 The entity class is the component which the user directly interact with. Player character and other
	 input based characters are derived from this.

	 You can imagine entities as a soul. You are required to control it. 
	 An entity is a collection of data to store a complete entity in a game. 
	 A basic entity contains:
	   - Shaders
	   - Meshes
	     - Materials
		   - Textures
	   - Uniform Buffer Objects
	   - Audio Components
	   - Physics Bodies

	 @warn: Entities that are not in the game world must be externally initialized.
	*/
	class DMK_API DMKGameEntity {
	public:
		DMKGameEntity() {}
		virtual ~DMKGameEntity() {}

		/*
		 Setup the current level.
		 This function is handled internally!

		 @param pCurrentLevel: Pointer to the current level component.
		*/
		void setupCurrentLevel(DMKLevelComponent* pCurrentLevel);

		/*
		 Initialize the entity
		*/
		virtual void initialize() {}

		// void addInstance(Vector3F position, Vector3F rotation);

		/*
		 Add a material to every requested component in the entity.
		 @warn: The component requires to be a renderable component. Else this function may fail.

		 @param material: The material to be added.
		 @tparam COMPONENT: The component to be added.
		*/
		template<class COMPONENT>
		DMK_FORCEINLINE void addMaterial(const DMKMaterial& material)
		{
			for (UI64 index = 0; index < getComponentArray<COMPONENT>()->size(); index++)
				getComponent<COMPONENT>(index)->addMaterial(material);
		}

		/*
		 Update method used to update components.
		*/
		virtual void onUpdate(F32 timeStep) {}

		/*
		 Setup camera module
		 Camera modules are added to the renderable components after initializing the entity.
		 Shaders will have the uniform buffer of the camera at the last binding. by default view and 
		 projection matrices are passed respectively.
		*/
		virtual void setupCamera(const DMKCameraModule* pCameraModule);

		/*
		 Add a component to the component manager.

		 @param component: The component to be added.
		 @tparam COMPONENT: The component type.
		*/
		template<class COMPONENT>
		DMK_FORCEINLINE void addComponent(const COMPONENT& component)
		{
			componentManager.addObject<COMPONENT>(component);
		}

		/*
		 Add multiple components of the same type to the component manager.

		 @param components: The array of components.
		 @tparam COMPONENT: The component type.
		*/
		template<class COMPONENT>
		DMK_FORCEINLINE void addComponents(ARRAY<COMPONENT> components)
		{
			componentManager.addObjects<COMPONENT>(components);
		}

		/*
		 Get a component from the component manager.

		 @param index: Component index.
		 @tparam COMPONENT: Component type.
		*/
		template<class COMPONENT>
		DMK_FORCEINLINE COMPONENT* getComponent(UI64 index = 0)
		{
			return componentManager.getObject<COMPONENT>(index);
		}

		/*
		 Get the component array.

		 @tparam COMPONENT: The required component.
		*/
		template<class COMPONENT>
		DMK_FORCEINLINE ObjectArrayType<COMPONENT>* getComponentArray()
		{
			return componentManager.getObjectArray<COMPONENT>();
		}

		/* Component Manager */
		ObjectArray componentManager;

		/* Shader modules of the entity */
		ARRAY<DMKShaderModule> shaders;

		B1 isCameraAvailable = false;

	protected:	/* Protected Data */
		DMKCameraModule* pCameraModule = nullptr;
		DMKLevelComponent* pCurrentLevel = nullptr;

	private:	/* Internal Data */
	};
}

#endif // !_DYNAMIK_GAME_ENTITY_H
