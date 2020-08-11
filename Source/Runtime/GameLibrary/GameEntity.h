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
	class DMK_API DMKGameModule;
	class DMK_API DMKGameEntity;

	/* Dynamik Game Entity Instance */
	struct DMK_API DMKGameEntityInstance {
		DMKGameEntityInstance() = default;
		DMKGameEntityInstance(const STRING& name, const Vector3F& position, const Quaternion& rotation, const Vector3F& scale, DMKGameEntity* pParentEntity) :
			name(name), position(position), rotation(rotation), scale(scale), pParentEntity(pParentEntity) {}

		STRING name = TEXT("");
		Quaternion rotation = Quaternion(0.0f);
		Vector3F position = Vector3F::ZeroAll;
		Vector3F scale = Vector3F::ZeroAll;

		DMKGameEntity* pParentEntity = nullptr;
	};

	/*
	 Dynamik Game Entity
	 Entities are fixed and/ or user definable objects which batch components together to form one single unit. 
	 Usually these entities are used to define an element in the game world. The engine contains a number of 
	 Data are added to these entities using components which contain sub-components which defines them.
	*/
	class DMK_API DMKGameEntity {
	public:
		DMKGameEntity() = default;
		virtual ~DMKGameEntity() = default;

		/*
		 Setup the current level.
		 This function is handled internally!

		 @param pCurrentModule: Pointer to the current level component.
		*/
		void setupCurrentModule(DMKGameModule* pCurrentModule);

		/*
		 Initialize the entity
		*/
		virtual void initialize() {}

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

		STRING entityName = TEXT("");

	public:
		/*
		 Add an instance of the current entity. 
		 This makes a direct copy of this entity and places it at another position in the world space with its own 
		 position, rotation, scale and name.

		 @param name: The name of the instance.
		 @param position: The position of the instance in the game world.
		 @param rotation: The rotation of the instance in the game world. Default is 0.0f.
		 @param scale: The scale of the instance in the game world. Default is 0.0f.
		*/
		void addInstance(const STRING& name, const Vector3F& position, const Quaternion& rotation = Quaternion(0.0f), const Vector3F& scale = Vector3F::ZeroAll);

		/*
		 Get an instance at a given index.
		*/
		DMKGameEntityInstance* getInstance(I64 index);

		/* All the instances */
		ARRAY<DMKGameEntityInstance> instances;

	protected:	/* Protected Data */
		DMKCameraModule* pCameraModule = nullptr;
		DMKGameModule* pCurrentModule = nullptr;
	};

	/*
	* 
	* In the studio, users are to add entities by right clicking on the module editor and selecting add entity. Then 
	* a few options will be available. Some of them are,
	*   - Create Custom Entity
	*   - Create StaticModel Entity
	*   - Create AnimatedModel Entity
	*   - Create Canvas Entity
	* 
	*/
}

#endif // !_DYNAMIK_GAME_ENTITY_H
