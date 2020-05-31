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

#include "Managers/Window/WindowManager.h"
#include "Managers/GameComponent/GameComponentManager.h"
#include "Managers/Thread/ThreadManager.h"

#include "Utilities/Clock.h"
#include "GameLibrary/LevelComponent.h"

namespace Dynamik
{
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
	};

	/*
	 This class provides all the necessary interfaces for the user to control the core components
	 of the Dynamik Engine.

	 Users are required to follow some steps to properly initialize and execute their game code from this engine.
	 These steps are as follows:
	 * Create the engine 
	 * Create a window object (this is optional as the engine will create a window if not created).
	 * Initialize internal components of the engine.
	 * Set default camera if needed.
	 * Submit level(s).

	 <When rendering a scene>
	 * Load scene data.
	 * Generate renderables.
	 * Finalize the renderables.
	 * Call the main loop.

	 <When shutting down>
	 * Terminate renderables.
	 * Unload Level.
	 * Terminate engine components.
	 * Terminate engine 
	*/
	class DMK_API DMKEngine {
	public:
		DMKEngine();
		~DMKEngine();

		/*
		 Create a new engine 
		 Since Dynamik only allows to instanciate one engine instance at a time, calling this function in the
		 presence of a valid instance will result to a warning and would not create a new  If required
		 to create a new instance while the engine is instantiated, the engine must be terminated successfully
		 to do so.
		*/
		void createInstance(DMKEngineInstanceDescriptor descriptor);

		/*
		 Add levels to the engine.
		*/
		void setLevels(ARRAY<POINTER<DMKLevelComponent>> levelComponents);

		/*
		 Main run loop.
		*/
		void execute();

	private:
		STRING myBasePath = DMK_TEXT("");

		DMKWindowManager _windowManager;
		DMKThreadManager _threadManager;
		DMKClock _clock;
		DMKGameComponentManager _gameComponentManager;
	};
}

#endif // !_DYNAMIK_H
