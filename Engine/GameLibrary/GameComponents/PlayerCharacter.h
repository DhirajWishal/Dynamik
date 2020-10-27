// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_LIBRARY_PLAYER_CHARACTER_H
#define _DYNAMIK_GAME_LIBRARY_PLAYER_CHARACTER_H

#include "GameCharacter.h"

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * The player character for the Dynamik Engine.
		 * This object contains a camera module and gets user inputs.
		 */
		class PlayerCharacter : public GameCharacter {
		public:
			/**
			 * Default constructor.
			 */
			PlayerCharacter() {}

			/**
			 * Default destructor.
			 */
			virtual ~PlayerCharacter() {}
		};
	}
}

#endif // !_DYNAMIK_GAME_LIBRARY_PLAYER_CHARACTER_H
