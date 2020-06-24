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

#include "Utilities/Clock.h"

#include "GameLibrary/GamePackage.h"

namespace Dynamik
{
	/*
	 Primary window information
	*/
	struct DMK_API DMKPrimaryWindowDescription {
		STRING title = DMK_TEXT("Dynamik Engine");
		UI32 width = 1280;
		UI32 height = 720;
	};

	/*
	 Dynamik Engine Instance Descriptor
	 This object is used to create and initialize the Dynamik Engine.
	*/
	class DMK_API DMKEngineInstanceDescriptor {
	public:
		DMKEngineInstanceDescriptor() {}
		~DMKEngineInstanceDescriptor() {}

		STRING applicationName = DMK_TEXT("Dynamik Engine v1");
		/* Versioning: (Major-Minor-Patch)*/
		STRING applicationVersion = DMK_TEXT("00001-00001-00000");
		STRING iconPath = DMK_TEXT("");

		DMKPrimaryWindowDescription windowDescription;
		DMKRenderingAPI renderingAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;
	};

	/*
	 This class provides all the necessary interfaces for the user to control the core components
	 of the Dynamik Engine.

	 Basic steps:
	 * Instanciate the engine by providing the instance descriptor and the game package.
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
		DMKEngine(const DMKEngineInstanceDescriptor& instanceDescriptor, const DMKGamePackage* gamePackage);

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

	private:	/* Client game data store */
		DMKGamePackage* _gamePackage;
		DMKLevelComponent* _currentLevel;
		DMKLevelComponent* _nextLevel;
		UI64 _nextLevelIndex = 0;

	private:	/* Private runtime data store */
		STRING myBasePath = DMK_TEXT("");

		DMKWindowManager _windowManager;
		DMKThreadManager _threadManager;
		DMKClock _clock;
		DMKEngineInstanceDescriptor _instanceDescription;

		UI32 _levelIndex = 0;
	};
}

#endif // !_DYNAMIK_H
