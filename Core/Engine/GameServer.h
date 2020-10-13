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

class DMK_API DMKRenderer;

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
 like the other systems. The engine is built on the game server which means that the game itself is the engine.

 Users are needed to initialize the required systems which the game requires. This means that initializing, updating 
 and terminating systems are done by the user.
*/
class DMK_API DMKGameServer {
public:
	DMKGameServer();
	virtual ~DMKGameServer();

	/* User defined methods */
protected:
	/* USER DEFINED
	 On initialize systems method. 
	 This is the first method to be called and user is expected to initialize all the runtime systems (renderer, 
	 audio engine, physics engine, window handle, etc...) in this method. 
	*/
	virtual void onInitializeSystems() {}

	/* USER DEFINED
	 On initialize services method. 
	 This method is used to initialize the services required by the game. 
	*/
	virtual void onInitializeServices() {}

	/* USER DEFINED
	 On initialize game method. 
	 This method is called right after calling the onInitializeSystems() method. User can use this method to initialize 
	 the game and even to load a game module. 
	*/
	virtual void onInitializeGame() {}

	/* USER DEFINED
	 On initialize final method. 
	 This method is called prior to entering the main execution loop. 
	*/
	virtual void onInitializeFinal() {}

	/* USER DEFINED
	 On begin update method.
	 This method is called once the engine enters a new main loop iteration.
	*/
	virtual void onBeginUpdate() {}

	/* USER DEFINED
	 On update game method. 
	 This method is called right after calling the onBeginUpdate() method. User is expected to update the game using 
	 this method (the game code and calling the updateCurrentGameModule() method). 
	*/
	virtual void onUpdateGame() {}

	/* USER DEFINED
	 On update systems method. 
	 User is required to update the relevant systems explicitly using this method. 
	*/
	virtual void onUpdateSystems() {}

	/* USER DEFINED
	 On end update method.
	 This method will be called right before finishing the main loop iteration.
	*/
	virtual void onEndUpdate() {}

	/* USER DEFINED
	 On terminate game method. 
	 This method is called right after exiting the main execution loop. The game is expected to be terminated using
	 this method.
	*/
	virtual void onTerminateGame() {}

	/* USER DEFINED
	 On terminate systems method. 
	 The user is expected to terminate all the initialized and/ or used systems in this method. 
	*/
	virtual void onTerminateSystems() {}

	/* USER DEFINED 
	 On terminate services method. 
	 User is expected to terminate the relevant services using this method. 
	*/
	virtual void onTerminateServices() {}

	/* USER DEFINED
	 On terminate final method. 
	 This method is called prior to shutting down the server completely. 
	*/
	virtual void onTerminateFinal() {}

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
	 Get the currently active player controller. 
	*/
	DMKPlayerController* getPlayerController() const;

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

	/*
	 Main public methods
	 These methods are not intended to be used by the user but to be used by the engine instance.
	*/
public:
	/* PUBLIC
	 Initialize the engine.
	*/
	void initialize();

	/* PUBLIC
	 The main loop of the engine.
	*/
	void execute();

	/* PUBLIC
	 Terminate the engine.
	*/
	void terminate();

	/* Internal protected methods */
protected:
	/*
	 Initialize the event pool. 
	*/
	void initializeEventPool();

	/*
	 Initialize the player controller. 
	*/
	void initializePlayerController();

	/*
	 Initialize the rendering engine. 

	 @param description: The renderer description to initialize the rendering engine. 
	*/
	void initializeRenderingEngine(const DMKRendererDescription& description = DMKRendererDescription());

	/*
	 Terminate the rendering engine.
	*/
	void terminateRenderingEngine();

	/*
	 Initialize the window handle.
	*/
	void initializeWindowHandle();

	/*
	 Terminate the window handle. 
	*/
	void terminateWindowHandle();

	/*
	 Initialize the basic services of the engine. 
	 These include factories, utilities, etc..
	*/
	void initializeBasicServices();

	/*
	 Terminate the basic services. 
	*/
	void terminateBasicServices();

	/*
	 Initialize the asset registry. 
	*/
	void initializeAssetRegistry();

	/*
	 Initialize the tools registry. 
	*/
	void initializeToolsRegistry();

	/* Internal helper methods */
private:
	/*
	 Create a window.

	 @param width: The initial width of the window.
	 @param height: The initial height of the window.
	 @param title: The title of the window.
	*/
	DMKWindowHandle* createWindow(UI64 width, UI64 height, const STRING& title);

	/*
	 Initialize the game world.
	*/
	void initializeGameWorld();

	/* Internal data store */
private:
	/* Internal clock */
	DMKClock clock;

	/* Internal active window handle */
	DMKWindowHandle* pActiveWindowHandle = nullptr;
};

/* Main entry point for the game. */
#define DMK_SETUP_SERVER(GameServer)											\
	int main(int argc, char* argv[])											\
	{																			\
		try																		\
		{																		\
			GameServer gameServer;												\
																				\
			/* Initialize the engine. */										\
			gameServer.initialize();											\
																				\
			/* Execute the engine. */											\
			gameServer.execute();												\
																				\
			/* Terminate the engine. */											\
			gameServer.terminate();												\
		}																		\
		catch (const std::exception& e)											\
		{																		\
			DMKErrorManager::logFatal(e.what(), __FILE__, __LINE__);			\
			return -1;															\
		}																		\
																				\
		return 0;																\
	}									

#endif // !_DYNAMIK_GAME_SERVER_H
