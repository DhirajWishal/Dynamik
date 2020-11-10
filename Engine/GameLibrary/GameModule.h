// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_MODULE_H
#define _DYNAMIK_GAME_MODULE_H

#include "Core/Macros/Global.h"

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Game module for the Dynamik Engine.
		 * This object represents a single level in a game and contains the main game logic.
		 */
		class GameModule {
		public:
			/**
			 * Default constructor.
			 */
			GameModule() {}

			/**
			 * Default destructor.
			 */
			virtual ~GameModule() {}
		};
	}
}

#endif // !_DYNAMIK_GAME_MODULE_H
