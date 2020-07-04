// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_H
#define _DYNAMIK_H

/*
 Main Dynamik Engine Interface.
 This file contains all the necessary engine interfaces provided by the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"
#include "Core/Globals/RenderSettings.h"

#include "Managers/Window/WindowManager.h"
#include "Managers/Thread/ThreadManager.h"

#include "Core/Utilities/Clock.h"

#include "GameLibrary/GamePackage.h"

#include "Services/RuntimeSystems/ConfigurationService.h"

namespace Dynamik
{
	/*
	 This class provides all the necessary interfaces for the user to control the core components
	 of the Dynamik Engine.

	 Basic steps:
	 * Instantiate the engine by providing the instance descriptor and the game package.
	 * Call the initialize method.
	 * Call the execute method.
	 * Call the terminate method.
	*/
	class DMK_API DMKEngine {
	public:
		/*
		 Default Constructor
		 This initializes all the components of the engine.
		*/
		DMKEngine(const DMKGamePackage* gamePackage);

		/*
		 Main run loop.
		*/
		void execute();

		/*
		 Default Destructor
		 This shuts down all the engine components and game code.
		*/
		~DMKEngine();

	private:	/* Private runtime functions */
		void _initializeRuntimeSystems();
		void _loadLevel();
		DMKWindowHandle* _createWindow(I32 width, I32 height, STRING title);

	private:	/* Client game data store */
		DMKGamePackage* pGamePackage = nullptr;
		DMKLevelComponent* pCurrentLevel = nullptr;
		DMKLevelComponent* pNextLevel = nullptr;
		DMKEventBoard myEventBoard;
		UI64 _nextLevelIndex = 0;

	private:	/* Private runtime data store */
		STRING myBasePath = DMK_TEXT("");

		DMKWindowHandle* pActiveWindow = nullptr;

		DMKThreadManager _threadManager;
		DMKClock _clock;

		UI32 _levelIndex = 0;

	private:	/* Engine Runtime Utilities */
	};
}

/* Main entry point for the game. */
#define DMK_ENTRY_POINT(GamePackage)											\
	int main()																	\
	{																			\
		try																		\
		{																		\
			GamePackage _package;												\
																				\
			/* Instantiate the engine */										\
			Dynamik::DMKEngine _engine(&_package);								\
																				\
			/* Execute the engine */											\
			_engine.execute();													\
																				\
		}																		\
		catch (const std::exception& e)											\
		{																		\
			Dynamik::DMKErrorManager::logFatal(e.what(), __FILE__, __LINE__);	\
			return -1;															\
		}																		\
																				\
		return 0;																\
	}									

#endif // !_DYNAMIK_H
