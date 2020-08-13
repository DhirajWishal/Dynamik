// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_SERVER_H
#define _DYNAMIK_GAME_SERVER_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"
#include "Core/Globals/RenderSettings.h"

#include "Managers/Window/WindowManager.h"

#include "Core/Utilities/Clock.h"

#include "GameLibrary/GameModule.h"

#include "Services/RuntimeSystems/ConfigurationService.h"

#include "Renderer/Renderer.h"

namespace Dynamik
{
	/*
	 Dynamik Game Data 
	 This structure contains all the information related to a game.
	*/
	struct DMK_API DMKGameData {
		STRING gameName = TEXT("Dynamik Engine");
		STRING gameTitle = TEXT("");
	};

	/*
	 Dynamik Game Server
	 This is the main game engine instance and the base class for the user game application.

	 Dynamik is composed of multiple servers/ systems. Basically this means that each of these systems run on its own
	 thread and handles its own data much like a server. The engine is the main system which also acts as a server just
	 like the other systems which initialize, manage, update and terminates these systems. The engine is built on the
	 game server which means that the game itself is the engine. Much of the internal methods used by the engine runtime
	 is abstracted out and is unavailable to the user but some methods are exposed to help the user in some tasks.
	 The thread running the game code is also known as the parent thread or the game thread.
	*/
	class DMK_API DMKGameServer {
	public:
		DMKGameServer();
		virtual ~DMKGameServer();

		/* User defined methods */
	protected:
		/* USER DEFINED
		 On initialize stage one method.
		 This method is called after initializing all the runtime systems.
		*/
		virtual void onInitializeStageOne() {}

		/* USER DEFINED
		 On initialize stage two method.
		 This method is called right after initializing the services. 
		*/
		virtual void onInitializeStageTwo() {}

		/* USEER DEFINED 
		 On initialize stage three.
		 This method is called right before entering the main loop.
		*/
		virtual void onInitializeStageThree() {}

		/* USER DEFINED
		 On begin update method.
		 This method is called once the engine enters a new main loop iteration.
		*/
		virtual void onBeginUpdate() {}

		/* USER DEFINED
		 On update method.
		 This method is called right before updating the currently loaded module.
		*/
		virtual void onUpdate(const F32 frameTime) {}

		/* USER DEFINED 
		 On end update method.
		 This method will be called right before finishing the main loop iteration.
		*/
		virtual void onEndUpdate() {}

		/* USER DEFINED
		 On terminate method. This method is called right after termination the runtime systems.
		*/
		virtual void onTerminate() {}

		/* Helper methods */
	protected:
		/* HELPER 
		 Set the game data. 

		 @param gameData: The game data structure.
		*/
		void setGameData(const DMKGameData& gameData);

		/* HELPER 
		 Get the current game data.
		*/
		DMKGameData& getGameData() const;

		/* HELPER 
		 Load a game module.
		 This method checks if a game module is currently active and if true, it terminates it and swaps it with the
		 newly specified module.

		 @param pModule: The game module to be loaded.
		*/
		void loadGameModule(DMKGameModule* pModule);

		/* HELPER
		 Get the currently active module.
		*/
		DMKGameModule* getActiveGameModule() const;

		/* HELPER
		 Returns the currently active rendering engine.
		*/
		DMKRenderer* getRenderer() const;

		/* HELPER 
		 Get the active clock.
		*/
		DMKClock& getClock() const;

		/* HELPER 
		 Get the current window handle.
		*/
		DMKWindowHandle* getCurrentWindowHandle() const;

		/* Protected data store */
	protected:
		/* Game data structure */
		DMKGameData gameData;

		/* The active game module */
		DMKGameModule* pActiveGameModule = nullptr;

		/* Main internal methods */
	private:
		/* INTERNAL
		 Initialize the engine.
		*/
		void initialize();

		/* INTERNAL
		 The main loop of the engine.
		*/
		void execute();

		/* INTERNAL
		 Terminate the engine.
		*/
		void terminate();

		/* Internal helper methods */
	private:
		/*
		 Initialize the runtime systems of the engine. 
		*/
		void initializeRuntimeSystems();

		/*
		 Initialize the services of the engine. 
		*/
		void initializeServices();

		/* 
		 Initialize the window handle.
		*/
		void initializeWindowHandle();

		/*
		 Create a window. 

		 @param width: The initial width of the window.
		 @param height: The initial height of the window.
		 @param title: The title of the window.
		*/
		DMKWindowHandle* createWindow(UI64 width, UI64 height, const STRING& title);

		/*
		 Submit all the game world data.
		*/
		void submitGameWorldData();

		/* Internal data store */
	private:
		/* Internal clock */
		DMKClock clock;

		/* Internal event pool */
		DMKEventPool eventPool;

		/* Internal active window handle */
		DMKWindowHandle* pActiveWindowHandle = nullptr;
	};
}

/* Main entry point for the game. */
#define DMK_SETUP_SERVER(GameServer)											\
	int main(int argc, char* argv[])											\
	{																			\
		try																		\
		{																		\
			GameServer gameServer = {};											\
		}																		\
		catch (const std::exception& e)											\
		{																		\
			Dynamik::DMKErrorManager::logFatal(e.what(), __FILE__, __LINE__);	\
			return -1;															\
		}																		\
																				\
		return 0;																\
	}									

#endif // !_DYNAMIK_GAME_SERVER_H
