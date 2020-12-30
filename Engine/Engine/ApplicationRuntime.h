// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ENGINE_APPLICATION_RUNTIME_H
#define _DYNAMIK_ENGINE_APPLICATION_RUNTIME_H

#include "GameApplication.h"

#include <type_traits>

namespace DMK
{
	namespace Engine
	{
		/**
		 * Applciation Runtime object.
		 * This object is the main object which executes the game application.
		 */
		template<class Type>
		class ApplicationRuntime {

			// Check if the game applciation type is derived from the DMK::Engine::GameApplciation object.
			static_assert(
				std::is_base_of<GameApplication, Type>::value,
				"The submitted Game Applciation object is not derived from the DMK::Engine::GameApplication "
				"object. The engine requires the game application to be derived from the GameApplication object!"
				);

		public:
			/**
			 * Default constructor.
			 * This method initialized the application object with predefined initializer values if needed.
			 *
			 * @param args: The VA arguments which are required by the game application.
			 */
			template<class... Args>
			ApplicationRuntime(Args&&... args) : applciation(Type(args...)) {}

			/**
			 * Default destructor.
			 */
			virtual ~ApplicationRuntime() {}

			/**
			 * Initialize the game application.
			 * This method initializes the application in the following order,
			 * - Initialize internals.
			 * - Initialize services.
			 * - Initialize systems.
			 * - Initialize game.
			 * - Initialize finals.
			 */
			void Initialize()
			{

			}

		private:
			Type mApplciation;	// Game application instance.
		};
	}
}

#define SETUP_GAME_APPLICATION(Object, ...)

#endif // !_DYNAMIK_ENGINE_APPLICATION_RUNTIME_H
