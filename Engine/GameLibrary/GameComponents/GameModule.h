// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_MODULE_H
#define _DYNAMIK_GAME_MODULE_H

#include "GameCharacter.h"

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Game Module for the Dynamik Engine.
		 * This object contains the game logic and the game world state.
		 *
		 * Components of the game world are loaded as properties just like with the game characters. These properties
		 * are static and does not contain any functionalities.
		 */
		class GameModule : public GameComponent {
		public:
			/**
			 * Default constructor.
			 */
			GameModule() {}

			/**
			 * Default destructor.
			 */
			virtual ~GameModule() {}

			/**
			 * Spawn a character to the game world.
			 * This takes in the character type (the inherited object) and creates an instance of it, stores it in
			 * the memory and returns its pointer.
			 * This method calls the OnSpawn() method of game characters.
			 *
			 * Since these characters are stored in a dynamic array, the pointer returned by this method might not be
			 * valid after adding another character of the same type.
			 *
			 * @param location: The location in the game world which the character is spawned to.
			 * @param initData: The data to be initialized with. Default is Character().
			 * @tparam Character: The character type.
			 * @return: The pointer to the created character.
			 */
			template<class Character>
			Character* SpawnCharacter(const Vector3& location, const Character& initData = Character()) { return nullptr; }	//TODO
		};
	}
}

#endif // !_DYNAMIK_GAME_MODULE_H
