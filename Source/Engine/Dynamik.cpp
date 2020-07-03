// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

/*
 This file contains all the definitions of the Dynamik Engine interface.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "dmkafx.h"
#include "Dynamik.h"

#include "Core/Error/ErrorManager.h"
#include "Core/Utilities/Clock.h"
#include "Core/FileSystem/FileSystem.h"
#include "Core/Memory/AutomatedMemoryManager.h"
#include "Core/Object/Resource/ShaderFactory.h"

#include "Managers/Window/WindowManager.h"

#include "Importer/Dynamik/DAI/DAIObject.h"
#include "Importer/Asset/MeshImporter.h"

#include "GameLibrary/Utilities/MeshFactory.h"

namespace Dynamik
{
	/* Default constructor */
	DMKEngine::DMKEngine(const DMKGamePackage* gamePackage)
		: pGamePackage(Cast<DMKGamePackage*>(gamePackage))
	{
		_clock.start();
		pGamePackage->onLoad();

		_initializeRuntimeSystems();

		DMKErrorManager::logInfo("Welcome to the Dynamik Engine!");
		auto _localPath = DMKFileSystem::getExecutablePath();
		auto _workingDirectory = DMKFileSystem::getWorkingDirectory();
	 	DMKConfigurationService::openConfigFile(_workingDirectory + "/EngineConfig.ini");

		DMKMeshFactory::setWorkingDirectory(_workingDirectory);
		DMKShaderFactory::setWorkingDirectory(_workingDirectory);

		UI32 windowID = _windowManager.createWindow(1280, 720, "Dynamik Engine");	/* TODO */
		_threadManager.issueWindowHandleCommandRT(_windowManager.getWindowHandle(windowID));

		_threadManager.issueInitializeCommandRT();
		_threadManager.issueCreateContextCommandRT(DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT, _windowManager.createViewport(windowID, 512, 512, 0, 0));

		pGamePackage->onInit();

		_loadLevel();
	}

	/* Execute the game code */
	void DMKEngine::execute()
	{
		pGamePackage->onExecute();
		_threadManager.issueInitializeCameraCommandRT(pCurrentLevel->playerObject->getCameraModule());
		_threadManager.issueInitializeEnvironmentMapCommandRT(pCurrentLevel->environmentMap);
		_threadManager.issueInitializeLevelCommandRT(pCurrentLevel);
		_threadManager.issueInitializeFinalsCommandRT();

		UI64 _itrIndex = 0;
		DMKGameEntity* _entity = nullptr;

#ifdef DMK_DEBUG
		printf("Allocation count: %u\n", DMKAutomatedMemoryManager::getAllocationCount());

#endif // DMK_DEBUG

		while (true)
		{
			pGamePackage->onBeginFrame();

			_threadManager.clearCommands();

			_windowManager.pollEvents();

			pCurrentLevel->onUpdate(DMKEventBuffer());
			_threadManager.issueRawCommandRT(RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE);

			for (_itrIndex = 0; _itrIndex < pCurrentLevel->entities.size(); _itrIndex++)
			{
				pCurrentLevel->entities[_itrIndex];
				/* send entity to the physics engine */
			}

			_windowManager.clean();

			pGamePackage->onEndFrame();
		}
	}

	/* Default destructor */
	DMKEngine::~DMKEngine()
	{
		pGamePackage->onExit();

		DMKConfigurationService::writeWindowSize(_windowManager.getWindowHandle(0)->windowWidth, _windowManager.getWindowHandle(0)->windowHeight);
		_windowManager.terminateAll();

		DMKConfigurationService::closeConfigFile();
		_clock.end();
	}

	void DMKEngine::_initializeRuntimeSystems()
	{
		_threadManager.initializeBasicThreads();
	}

	void DMKEngine::_loadLevel()
	{
		pGamePackage->onLevelLoad(_nextLevelIndex);
		pCurrentLevel = pGamePackage->levels[_nextLevelIndex++];

		pCurrentLevel->onLoad();
		pCurrentLevel->initializeComponents();
		pCurrentLevel->setupEventMap(&_eventMap);

		for (auto _entity : pCurrentLevel->entities)
			_entity->initialize();

		pCurrentLevel->initializeCameraModule();
	}
}