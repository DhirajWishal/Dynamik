// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_ENTITY_H
#define _DYNAMIK_GAME_ENTITY_H

#include "GameComponent.h"
#include "Core/Maths/Vector/Vector3.h"
#include "Core/Macros/Global.h"

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Game Entity for the Dynamik Engine.
		 * All the game components which contains a functionality are defined using this object. Entitites are
		 * added to the game world state by spawining them.
		 *
		 * By default these objects only contain basic functionalities. By adding components, these objects are
		 * able to house multiple entities.
		 * There are 4 main types of components,
		 * - Graphics Component.
		 * - Physics Component.
		 * - Audio Component.
		 * - Input Component.
		 */
		class GameEntity : public GameComponent {
		public:
			GameEntity() {}
			virtual ~GameEntity() {}

			/**
			 * This method is called once the entity is spawned in the world state.
			 *
			 * @param location: The location to which the entity is spawned.
			 */
			virtual void OnSpawn(const Vector3& location) {}

			/**
			 * This method is called in the main loop iteration.
			 *
			 * @param timeStep: The time taken to execute the old iteration to this iteration.
			 */
			virtual void OnUpdate(float timeStep) {}

			/**
			 * This method is called when the entity is despawned from the game world state.
			 */
			virtual void OnDespawn() {}

			// Utilities.
		public:
			/**
			 * Get the entity casted to an inherited class.
			 *
			 * @tparam Type: The type to be casted to.
			 */
			template<class Type>
			DMK_FORCEINLINE constexpr Type* Inherit() { return dynamic_cast<Type*>(this); }
		};
	}
}

#endif // !_DYNAMIK_GAME_ENTITY_H
