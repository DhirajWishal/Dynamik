// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_COMPONENT_H
#define _DYNAMIK_GAME_COMPONENT_H

#include "GameLibrary/PropertySystem/PropertyStore.h"

namespace DMK
{
	namespace GameLibrary
	{
		/**
		 * Game Component for the Dynamik Engine.
		 * This object is the base class for all the main components of the game library.
		 *
		 * Properties are used to define certain chacracteristice of the component.
		 * Some of the properties are user editable, meaning that the user is allowed to inherit the base class and
		 * create it as their own to best fit them. But these require callback methods to initialize, update and terminate
		 * them.
		 */
		class GameComponent : public PropertyStore {
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
