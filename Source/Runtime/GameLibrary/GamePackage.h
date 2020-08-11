// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_PACKAGE_H
#define _DYNAMIK_GAME_PACKAGE_H

#include "GameModule.h"
#include "Core/Globals/RenderSettings.h"

namespace Dynamik
{
	/*
	 Dynamik Game Package
	 The client game application is passed to the engine using this object. Clients are required to derive
	 their own package from this and submit it to the engine upon instantiating.

	 Loading new modules are done using the package. Developers are required to instruct the engine to load the next 
	 module.
	*/
	class DMK_API DMKGamePackage {
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
		ARRAY<DMKGameModule*> modules;

	protected:
		void loadNextModule(DMKGameModule* pModule) {}

	public:		/* Engine Description */
		STRING applicationName = TEXT("Dynamik Engine v1");
		/* Versioning: (Major-Minor-Patch)*/
		STRING applicationVersion = TEXT("00001-00001-00000");
		STRING iconPath = TEXT("");

		DMKRenderingAPI renderingAPI = DMKRenderingAPI::DMK_RENDERING_API_VULKAN;

		/*
		 Basic game data
		*/
		STRING gameName = TEXT("Dynamik Engine");
		STRING gameDataPath = TEXT("");
		STRING gameAssetBasePath = TEXT("");
		UI64 gameVersion = 1;
	};	
}

#endif // !_DYNAMIK_GAME_PACKAGE_H
