// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_WORLD_H
#define _DYNAMIK_GAME_WORLD_H

#include "Core/Types/ComplexTypes.h"
#include "Core/Types/Utilities.h"
#include "Core/FileSystem/FileSystem.h"
#include "EnvironmentEntity.h"
#include "Services/SystemLocator.h"

#include "Renderer/Renderer.h"

namespace Dynamik
{
	class DMK_API DMKGameModule;

	/*
	 Interface Entity Array
	*/
	class DMK_API IEntityArray {
	public:
		IEntityArray() {}
		virtual ~IEntityArray() {}
	};

	/*
	 Type Entity Array
	 This object stores all the entities of a given type.
	*/
	template<class OBJECT>
	class DMK_API TEntityArray : public IEntityArray, public ARRAY<OBJECT> {
	public:
		TEntityArray() : ARRAY<OBJECT>() {}
		TEntityArray(UI64 size) : ARRAY<OBJECT>(size) {}
		TEntityArray(UI64 size, const OBJECT& value) : ARRAY<OBJECT>(size, value) {}
		TEntityArray(const OBJECT* arr) : ARRAY<OBJECT>(arr) {}
		TEntityArray(std::initializer_list<OBJECT> list, UI64 size = 1) : ARRAY<OBJECT>(list, size) {}
		TEntityArray(const ARRAY<OBJECT>& arr) : ARRAY<OBJECT>(arr) {}
		TEntityArray(ARRAY<OBJECT>&& arr) : ARRAY<OBJECT>(std::move(arr)) {}
		TEntityArray(std::vector<OBJECT> vector) : ARRAY<OBJECT>(vector) {}
		~TEntityArray() {}
	};

	/*
	 Dynamik Game World Light Component
	 This structure defines a global light component.
	*/
	struct DMK_API DMKGameWorldLightComponent {
		DMKColorComponent colorValue;
		Vector3F position = Vector3F(0.0f);
		Vector3F direction = Vector3F(0.0f);
	};

	/*
	 Dynamik Game World
	 This object represents a game world and may or may not contain behavior defined entities.
	*/
	class DMK_API DMKGameWorld {
	public:
		DMKGameWorld() = default;
		virtual ~DMKGameWorld() = default;

		/*
		 Initialize the game world.
		 This function will be called upon creation of the object (Only if the provided functions are used).
		 IF the world is created and assigned by the user, this function needs to be explicitly called.
		*/
		virtual void initialize() {}

		/*
		 On initialize entities method.
		 Users are to initialize all the entities and submit them to the relevant systems in this method.
		*/
		virtual void onInitializeEntities() {}

		/*
		 On update method.

		 @param timeStep: The amount of time elapsed from the last iteration.
		*/
		virtual void onUpdate(const F32 timeStep) {}

		/*
		 On main window resize method.
		 This method is called when the main window is resized. This method is also called when the main window is created.
		*/
		virtual void onMainWindowResize(DMKExtent2D newSize) {}

	public:		/* Entity Management */
		/*
		 Check if an entity is registered.

		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE B1 isEntityRegistered()
		{
			return registeredEntities.getNumberOfInstances(typeid(ENTITY).name()) > 0;
		}

		/*
		 Register a new entity.
		 This method checks is the entity is already registered. If true, it does not do anything.

		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE void registerEntity()
		{
			if (isEntityRegistered<ENTITY>())
			{
				DMK_WARN("The entity is already registered! Entity Name: " + STRING(typeid(ENTITY).name()));
				return;
			}

			STRING name = typeid(ENTITY).name();
			entityMap[name] = StaticAllocator<TEntityArray<ENTITY>>::allocate();
			registeredEntities.pushBack(name);
		}

		/*
		 Get the entity array stored in the object.
		 If the entity type is not registered, it automatically registers it.

		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE TEntityArray<ENTITY>* getEntities()
		{
			if (!isEntityRegistered<ENTITY>())
			{
				DMK_WARN("The entity is not registered! Creating a new array. Entity Name: " + STRING(typeid(ENTITY).name()));
				registerEntity<ENTITY>();
			}

			return Cast<TEntityArray<ENTITY>*>(entityMap[typeid(ENTITY).name()]);
		}

		/*
		 Add an entity to the entity array.

		 @param constructor: The value to be constructed with.
		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE void addEntity(const ENTITY& constructor = ENTITY())
		{
			getEntities<ENTITY>()->pushBack(constructor);
		}

		/*
		 Add an entity to the entity array.

		 @param constructor: The value to be constructed with.
		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE void addEntity(ENTITY&& constructor)
		{
			getEntities()->pushBack(std::move(constructor));
		}

		/*
		 Get an entity in the entity array.

		 @param index: The index of the entity Default is 0.
		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE ENTITY* getEntity(I64 index = 0)
		{
			return Cast<ENTITY*>(getEntities<ENTITY>()->location(index));
		}

		/*
		 Get the number of entities stored in the entity array.

		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE UI64 getEntityCount() const
		{
			return getEntities<ENTITY>()->size();
		}

		/*
		 Get all of the registered entity names.
		*/
		DMK_FORCEINLINE ARRAY<STRING> getAllRegisteredEntityNames() const { return this->registeredEntities; }

		/* Helper methods to initialize entities */
	protected:
		/*
		 Setup player controls.
		 This method is to be called with a valid player entity submitted to the entity registry on the onInitializeEntities()
		 method. Since multiple player entities can be stored, the index of the required entity is needed.

		 @param index: The index of the player entity. Default is 0.
		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE void setupPlayerConstrols(I64 index = 0)
		{
			auto pEntity = getEntity<ENTITY>(index);

			if (!isInheritedFrom<DMKPlayerEntity>(pEntity))
				return;

			pEntity->setupPlayerControls(DMKSystemLocator::getSystem<DMKPlayerController>());
		}

		/*
		 Submit the static model to the renderer. 

		 @param index: The index of the entity.
		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE void submitStaticModelToRenderer(I32 index = 0)
		{
			auto pEntity = getEntity<ENTITY>(index);

			if (!isInheritedFrom<DMKStaticModelEntity>(pEntity))
				return;

			DMKSystemLocator::getSystem<DMKRenderer>()->submitStaticModelEntityCMD(pEntity);
		}

		/*
		 Submit the static model to the renderer.

		 @param index: The index of the entity.
		 @tparam ENTITY: The entity type.
		*/
		template<class ENTITY>
		DMK_FORCEINLINE void submitAnimatedModelToRenderer(I32 index = 0)
		{
			auto pEntity = getEntity<ENTITY>(index);

			if (!isInheritedFrom<DMKAnimatedModelEntity>(pEntity))
				return;

			DMKSystemLocator::getSystem<DMKRenderer>()->submitAnimatedModelEntityCMD(pEntity);
		}

	private:
		/*
		 Internal method to check if an object is inherited from another. 

		 @param pEntity: The entity.
		 @tparam BASE: The base class to check from.
		 @tparam DERIVED: The class to be checked from.
		*/
		template<class BASE, class DERIVED>
		DMK_FORCEINLINE constexpr B1 isInheritedFrom(DERIVED* pEntity)
		{
			if (!IsInheritedFrom_C<BASE>(*pEntity))
			{
				DMK_ERROR("The submitted entity is not inherited from " + STRING(typeid(BASE).name()) + "! All player entities are required to be inherited from the " + typeid(BASE).name() + " object.");
				return false;
			}

			return true;
		}

		std::unordered_map<STRING, IEntityArray*> entityMap;
		ARRAY<STRING> registeredEntities;

	public:		/* Light Component */
		/* Global Light Components */
		ARRAY<DMKGameWorldLightComponent> globalLightComponents;

		void addLightComponent(DMKGameWorldLightComponent component);
	};

	/*

	 class BulletEntity final :
		// public DMKStaticModelEntity,				// Entity containing all the static model information.
		public DMKAnimatedModelEntity,				// Entity containing all the animated model information.
		public DMKAudioControllerEntity,			// Entity containing all the audio information.
		public DMKPhysicalEntity					// Entity containing all the physics information.
	 {
	  public:
		BulletEntity() {}
		~BulletEntity() {}

		virtual void onInitialize() override final
		{

		}
	 };

	 template<class ENTITY>
	 DMK_FORCEINLINE ENTITY* addEntity(const ENTITY& constructor)
	 {
		return entityManager.addObject<ENTITY>(constructor);
	 }


	 onInitialize()
	 {
		BulletEntity* pEntityOne = addEntity<BulletEntity>(BulletEntity());

		DMKSystemLocator::getSystem<DMKRenderer>::submitEntity(entityOne);

		for(UI32 index = 0; index < getEntityCount<BulletEntity>(); index++)
		{
			// Submit render data
			//DMKSystemLocator::getSystem<DMKRenderer>()->submitStaticModelEntity(getEntity<BulletEntity>(index));
			DMKSystemLocator::getSystem<DMKRenderer>()->submitAnimatedModelEntity(getEntity<BulletEntity>(index));

			// Submit audio data
			DMKSystemLocator::getSystem<DMKAudioPlayer>()->submitAudioEntity(getEntity<BulletEntity>(index));
		}
	 }

	 onUpdate()
	 {
		auto meshIndex = DMKSystemLocator::getSystem<DMKRenderer>()->submitMeshObjects(
			DMKMeshFactory::loadMesh("asset.obj", DMKVertexLayout::default()),
			DMKMeshRenderSpecification::createBasic(DMKShaderFactory::createBasic()));

		auto audioIndex = DMKSystemLocator::getSystem<DMKAudioController>()->submitAudioObjects(
			DMKAudioLoader::loadFromFile("asset.mp3"));

		DMKSystemLocator::getSystem<DMKAudioController>()->playOnce(index, volume, sphereRadius);

		DMKSystemLocator::getSystem<DMKRenderer>()->unloadMeshObject(meshIndex);
	 }
	*/
}

#endif // !_DYNAMIK_GAME_WORLD_H
