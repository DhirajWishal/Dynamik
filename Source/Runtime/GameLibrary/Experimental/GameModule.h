// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_EXPERIMENTAL_GAME_MODULE_H
#define _DYNAMIK_EXPERIMENTAL_GAME_MODULE_H

#include "Core/Types/Array.h"
#include "Events/GameEvents.h"
#include "GameLibrary/Mechanics/PlayerController.h"

namespace Dynamik
{
	namespace Experimental
	{
		/*
		 Interface Game Entity Array Base object
		 This object it the base class for the game entity array.
		*/
		class DMK_API IGameEntityArrayBase {
		public:
			IGameEntityArrayBase() = default;
			virtual ~IGameEntityArrayBase() = default;
		};

		/*
		 Dynamik Game Entity Array
		 This object stores all the necessary game entity data.
		*/
		template<class OBJECT>
		class DMK_API DMKGameEntityArray : public IGameEntityArrayBase, public ARRAY<OBJECT> {
		public:
			DMKGameEntityArray() : ARRAY<OBJECT>() {}
			DMKGameEntityArray(UI64 size) : ARRAY<OBJECT>(size) {}
			DMKGameEntityArray(UI64 size, const OBJECT& value) : ARRAY<OBJECT>(size, value) {}
			DMKGameEntityArray(const OBJECT* arr) : ARRAY<OBJECT>(arr) {}
			DMKGameEntityArray(std::initializer_list<OBJECT> list, UI64 size = 1) : ARRAY<OBJECT>(list, size) {}
			DMKGameEntityArray(const ARRAY<OBJECT>& arr) : ARRAY<OBJECT>(arr) {}
			DMKGameEntityArray(ARRAY<OBJECT>&& arr) : ARRAY<OBJECT>(std::move(arr)) {}
			DMKGameEntityArray(std::vector<OBJECT> vector) : ARRAY<OBJECT>(vector) {}
			~DMKGameEntityArray() {}
		};

		/*
		 Dynamik Game Module
		 This defines an actual game with all the data required for it. This object has the perspective of the player
		 and is loaded by the game package at runtime.

		 The player entity is a user definable entity which contains basic data (event callbacks, models, animations,
		 etc...) the player character contains.

		 The game world is an entity which is user definable and is loaded at runtime. This entity holds all the information
		 about the actual game world. World data are passed using scene objects. These objects are pre defined objects
		 which contains raw data. Components can be added to them to provide functionalities at runtime.
		*/
		class DMK_API DMKGameModule {
		public:
			DMKGameModule() {}
			virtual ~DMKGameModule() {}

		public:		/* Virtual Methods */
			virtual void onInitialize() {}
			virtual void onUpdate(const F32 timeStep) {}
			virtual void onTerminate() {}

			virtual void setupPlayerController(DMKPlayerController* pPlayerController) {}

		public:		/* Movement Controllers */
			virtual void onMoveForward() {}
			virtual void onMoveBackward() {}
			virtual void onMoveLeft() {}
			virtual void onMoveRight() {}

			virtual void onActionJump() {}
			virtual void onActionCrouch() {}
			virtual void onActionSprint() {}
			virtual void onActionAim() {}
			virtual void onActionBeginTrigger() {}
			virtual void onActionEndTrigger() {}

		public:		/* Entity Data Methods */
			/*
			 Check if an entity is already registered.

			 @tparam ENTITY: The entity type.
			*/
			template<class ENTITY>
			DMK_FORCEINLINE B1 isRegistered()
			{
				return registeredEntityTypes.getNumberOfInstances(typeid(ENTITY).name()) > 0;
			}

			/*
			 Register an entity to the game module.
			 This method will check if the entity actually exists and if not, it registers it.

			 @tparam ENTITY: The entity type.
			*/
			template<class ENTITY>
			DMK_FORCEINLINE void registerEntity()
			{
				if (isRegistered<ENTITY>())
				{
					DMK_ERROR("The entity is already registered!");
					return;
				}

				STRING name = typeid(ENTITY).name();

				entityMap[name] = StaticAllocator<DMKGameEntityArray<ENTITY>>::allocate();
				registeredEntityTypes.pushBack(name);
			}

			/*
			 Get the entity array of a given entity. 
			 It automatically registers the entity if it is not available.

			 @tparam ENTITY: The entity type.
			*/
			template<class ENTITY>
			DMK_FORCEINLINE DMKGameEntityArray<ENTITY>* getEntityArray()
			{
				if (!isRegistered())
					registerEntity<ENTITY>();

				return Cast<DMKGameEntityArray<ENTITY>*>(entityMap[typeid(ENTITY).name()]);
			}

			/*
			 Add an entity to the entity array. 

			 @param entity: The entity data that needs to be passed.
			 @tparam ENTITY: The entity type.
			*/
			template<class ENTITY>
			DMK_FORCEINLINE void addEntity(const ENTITY& entity)
			{
				getEntityArray<ENTITY>()->pushBack(entity);
			}

			/*
			 Get an entity from its entity array. 

			 @param index: The index of the entity in the array.
			 @tparam ENTITY: The entity type.
			*/
			template<class ENTITY>
			DMK_FORCEINLINE ENTITY* getEntity(UI64 index)
			{
				return Cast<ENTITY*>(getEntityArray<ENTITY>()->location(index));
			}

			/*
			 Get the size of the entity array. 

			 @tparam ENTITY: The entity type.
			*/
			template<class ENTITY>
			DMK_FORCEINLINE const UI64 getEntityArraySize()
			{
				return getEntityArray<ENTITY>()->size();
			}

			/*
			 Get all the registered entity type names. 
			*/
			ARRAY<STRING>& getAllRegisteredEntityNames() { return registeredEntityTypes; }

		protected:	/* Entity Array Store */
			std::unordered_map<STRING, IGameEntityArrayBase*> entityMap;
			ARRAY<STRING> registeredEntityTypes;
		};
	}
}

#endif // !_DYNAMIK_EXPERIMENTAL_GAME_MODULE_H
