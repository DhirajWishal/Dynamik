// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ENGINE_GAME_APPLICATION_H
#define _DYNAMIK_ENGINE_GAME_APPLICATION_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace Engine
	{
		/**
		 * Service initialization flags.
		 * These flags are used to initialize the required services.
		 */
		enum class ServiceInitializationFlags : UI8 {
			SHADER_TOOLS = BIT_SHIFT(0),
			ASSET_STORE = BIT_SHIFT(1),
		};

		/**
		 * System initialization flags.
		 * These flags are used to initialize the required systems.
		 */
		enum class SystemInitializationFlags : UI8 {
			GRAPHICS = BIT_SHIFT(0),
			AUDIO = BIT_SHIFT(1),
			PHYSICS = BIT_SHIFT(2),
			NETWORK = BIT_SHIFT(3),
		};

		/**
		 * Game Application object for the Dynamik Engine.
		 * This object is the main engine runtime instance. Users are required to create the game application using
		 * this object to initialize the basic components which will be used.
		 *
		 * The engine is made up of two main module types,
		 * - Systems.
		 * - Services.
		 *
		 * Systems are basically made of large, interconnected components which perform a complex task. Some examples
		 * are Graphics, Audio, Physics, etc...
		 * Services are componets which might not be necessary for the game's lifespan but contains functionalities which
		 * games might require. Some of these are Shader tools, Asset database, Analytics, etc...
		 *
		 * To execute the game, the user defined game application object is required to be submitted to the
		 * SETUP_GAME_APPLICATION() macro which contains the entry point for the application.
		 *
		 * All the methods stating USER DEFINED are required to be defined by the user game application.
		 */
		class GameApplication {
		public:
			GameApplication() {}
			virtual ~GameApplication() {}

			/**
			 * Initialize the application.
			 */
			void Initialize();

			/**
			 * Execute the application.
			 * This method contains the main game loop.
			 */
			void Execute();

			/**
			 * Terminate the game application.
			 */
			void Terminate();

		public:
			/** USER DEFINED
			 * Get the required service initialization flags.
			 *
			 * @return ServiceInitializationFlags enums containing the initialization flags.
			 */
			virtual ServiceInitializationFlags GetServiceInitializationFlags() const { return ServiceInitializationFlags(); }

			/** USER DEFINED
			 * Get the required system initialization flags.
			 *
			 * @return SystemInitializationFlags enums containing the initialization flags.
			 */
			virtual SystemInitializationFlags GetSystemInitializationFlags() const { return SystemInitializationFlags(); }

			/** USER DEFINED
			 * This method is to be used to initialize the game.
			 */
			virtual void InitializeGame() {}
		};

		DMK_FORCEINLINE ServiceInitializationFlags operator|(const ServiceInitializationFlags& lhs, const ServiceInitializationFlags& rhs)
		{
			return static_cast<ServiceInitializationFlags>(static_cast<UI8>(lhs) | static_cast<UI8>(rhs));
		}

		DMK_FORCEINLINE SystemInitializationFlags operator|(const SystemInitializationFlags& lhs, const SystemInitializationFlags& rhs)
		{
			return static_cast<SystemInitializationFlags>(static_cast<UI8>(lhs) | static_cast<UI8>(rhs));
		}
	}
}

/**
 * Main entry point macro.
 * This will call the main function and will execute the game code.
 *
 * @param GameApplication: The inherited game application class.
 * @param __VA_ARGS__: The arguments to be supplied to the class costructor.
 */
#define SETUP_GAME_APPLICATION(GameApplication, ...)		\
	int main(int argc, char** argv)							\
	{														\
		GameApplication application{__VA_ARGS__};			\
		application.Initialize();							\
		application.Execute();								\
		application.Terminate();							\
	}

#endif // !_DYNAMIK_ENGINE_GAME_APPLICATION_H
