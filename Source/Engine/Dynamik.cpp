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
#include "Core/Objects/Resource/ShaderFactory.h"
#include "Core/Math/MathFunctions.h"

#include "Managers/Window/WindowManager.h"
#include "Window/Windows/WindowsWindow.h"

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

		myEventPool.initialize();
		myPlayerController.setEventPool(&myEventPool);

		_initializeRuntimeSystems();

		DMKErrorManager::logInfo("Welcome to the Dynamik Engine!");
		auto _localPath = DMKFileSystem::getExecutablePath();
		auto _workingDirectory = DMKFileSystem::getWorkingDirectory();
		DMKConfigurationService::openConfigFile(_workingDirectory + "/EngineConfig.ini");

		DMKMeshFactory::setWorkingDirectory(_workingDirectory);
		DMKShaderFactory::setWorkingDirectory(_workingDirectory);

		pActiveWindow = _createWindow(1280, 720, "Dynamik Engine");
		_threadManager.issueWindowHandleCommandRT(pActiveWindow);

		_threadManager.issueInitializeCommandRT();
		_threadManager.issueCreateContextCommandRT(DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT, pActiveWindow->createViewport(512, 512, 0, 0));

		pGamePackage->onInit();

		_loadLevel();
	}

	/* Execute the game code */
	void DMKEngine::execute()
	{
		pGamePackage->onExecute();
		_threadManager.issueInitializeCameraCommandRT(pCurrentLevel->playerObject->getCameraModule());
		_threadManager.issueInitializeGameWorldCommandRT(pCurrentLevel->pCurrentGameWorld);
		_threadManager.issueInitializeFinalsCommandRT();

		UI64 _itrIndex = 0;
		DMKGameEntity* _entity = nullptr;

#ifdef DMK_DEBUG
		printf("Allocation count: %u\n", DMKAutomatedMemoryManager::getAllocationCount());

#endif // DMK_DEBUG

		while (!myEventPool.WindowCloseEvent)
		{
			pGamePackage->onBeginFrame();

			_threadManager.clearCommands();

			pActiveWindow->pollEvents();

			/* Check If The Frame Buffer Was Resized */
			if (myEventPool.FrameBufferResizeEvent)
			{
				pCurrentLevel->playerObject->setAspectRatio(pActiveWindow->getWindowExtent().width / pActiveWindow->getWindowExtent().height);
				_threadManager.issueFrameBufferResizeCommandRT(pActiveWindow->getWindowExtent());
				myEventPool.FrameBufferResizeEvent = false;
			}

			myPlayerController.executeAll();
			pCurrentLevel->onUpdate(&myEventPool);

			_threadManager.issueRawCommandRT(RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE);

			pActiveWindow->clean();

			pGamePackage->onEndFrame();
		}
	}

	/* Default destructor */
	DMKEngine::~DMKEngine()
	{
		pGamePackage->onExit();

		_threadManager.issueTerminateCommand();

		DMKConfigurationService::writeWindowSize(pActiveWindow->windowWidth, pActiveWindow->windowHeight);
		pActiveWindow->terminate();

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

		_initializeGameWorld();

		pCurrentLevel->initializeComponents();

		pCurrentLevel->setupPlayerControls(&myPlayerController);
	}

	void DMKEngine::_initializeGameWorld()
	{
		if (!pCurrentLevel->pCurrentGameWorld)
		{
			DMK_WARN("A game world has not been set!");
			return;
		}

		pCurrentLevel->pCurrentGameWorld->initializeEntities();
	}

	DMKWindowHandle* DMKEngine::_createWindow(I32 width, I32 height, STRING title)
	{
#ifdef DMK_PLATFORM_WINDOWS
		DMKWindowHandle* pHandle = StaticAllocator<WindowsWindow>::allocateInit(WindowsWindow(title, width, height));
		pHandle->initialize();
		pHandle->setEventBoard(&myEventPool);
		pHandle->initializeKeyBindings();
		pHandle->setEventCallbacks();

		return pHandle;

#endif // DMK_PLATFORM_WINDOWS

		return nullptr;
	}
}