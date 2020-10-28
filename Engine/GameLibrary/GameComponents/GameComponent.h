// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_COMPONENT_H
#define _DYNAMIK_GAME_COMPONENT_H

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Game Component for the Dynamik Engine.
		 * This object is the base class for all the main components of the game library.
		 */
		class GameComponent {
		public:
			/**
			 * Default constructor.
			 */
			GameComponent() {}

			/**
			 * Default destructor.
			 */
			virtual ~GameComponent() {}
		};
	}
}

#endif // !_DYNAMIK_GAME_COMPONENT_H
