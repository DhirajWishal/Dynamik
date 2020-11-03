// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_CHARACTER_H
#define _DYNAMIK_GAME_CHARACTER_H

#include "GameComponent.h"
#include "Core/Maths/Vector/Vector3.h"

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Game Character object for the Dynamik Engine.
		 * This object us the base class for all the characters in a game.
		 *
		 * Characters are objects which contains a certain behavior and playes a unique role in the game. Some
		 * examples for characters are,
		 * - Player
		 * - NPCs
		 * - Gun
		 * - Bullet
		 *
		 * Characters use properties to define what they contain. Some of these properties are.
		 * - Mesh Objects (defining the visual characteristics)
		 * - Audio Objects (defining the audio characteristics)
		 * - Physics Objects (defining the physical characteristics)
		 * - Trigger Objects (defining the events that can occur)
		 *
		 * These characters are spawned to the game world by the game module and are contained in a special storage.
		 */
		class GameCharacter : public GameComponent {
		public:
			/**
			 * Default constructor.
			 */
			GameCharacter() {}

			/**
			 * Default destructor.
			 */
			virtual ~GameCharacter() {}

			/**
			 * Virtual method defining what to do when the character is spawned to the game world.
			 *
			 * @param location: The location of the game world which the character is spawned to.
			 */
			virtual void OnSpawn(const Vector3& location) {}

			/**
			 * Virtual method defining what to do when the character is despawned from the game world.
			 */
			virtual void OnDespawn() {}
		};
	}
}

#endif // !_DYNAMIK_GAME_CHARACTER_H
