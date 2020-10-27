// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_LIBRARY_NON_PLAYER_CHARACTER_H
#define _DYNAMIK_GAME_LIBRARY_NON_PLAYER_CHARACTER_H

#include "GameCharacter.h"

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Non player character for the Dynamik Engine.
		 * This object does acts as an NPC which only contains a behaviour.
		 */
		class NonPlayerCharacter : public GameCharacter {
		public:
			/**
			 * Default constructor.
			 */
			NonPlayerCharacter() {}

			/**
			 * Default destructor.
			 */
			virtual ~NonPlayerCharacter() {}
		};
	}
}

#endif // !_DYNAMIK_GAME_LIBRARY_NON_PLAYER_CHARACTER_H
