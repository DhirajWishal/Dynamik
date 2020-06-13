// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_PACKAGE_H
#define _DYNAMIK_GAME_PACKAGE_H

/*
 Author:	Dhiraj Wishal
 Date:		04/06/2020
*/
#include "LevelComponent.h"

namespace Dynamik
{
	/*
	 Dynamik Game Package
	 The client game application is passed to the engine using this object. Clients are required to derive
	 their own package from this and submit it to the engine upon instantiating.
	*/
	class DMK_API DMKGamePackage  {
	public:
		DMKGamePackage() {}
		virtual ~DMKGamePackage() {}

		/*
		 This method is called once the package is taken in to the engine.
		*/
		virtual void onLoad() {}

		/*
		 This method is called after initializing the runtime systems.
		*/
		virtual void onInit() {}

		/*
		 This method is called when a new level is loaded to the memory.
		*/
		virtual void onLevelLoad(UI64 levelIndex) {}

		/*
		 This method is called right before the engine goes to its main loop.
		*/
		virtual void onExecute() {}

		/*
		 This method is called after the begin frame system is activated.
		*/
		virtual void onBeginFrame() {}

		/*
		 This method is called after the end frame system is activated.
		*/
		virtual void onEndFrame() {}

		/*
		 This method is called before the current level is unloaded.
		*/
		virtual void onLevelUnload(UI64 levelIndex) {}

		/*
		 This method is called before the engine is terminated.
		*/
		virtual void onExit() {}

		/*
		 All the levels in a game.
		*/
		ARRAY<POINTER<DMKLevelComponent>> levels;

		/*
		 Basic game data
		*/
		STRING gameName = DMK_TEXT("Dynamik Engine");
		UI64 gameVersion = 1;
		STRING gameDataPath = DMK_TEXT("");
		STRING gameAssetBasePath = DMK_TEXT("");
	};
}

#endif // !_DYNAMIK_GAME_PACKAGE_H
