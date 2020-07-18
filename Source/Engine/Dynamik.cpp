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
#include "Core/Utilities/ShaderFactory.h"
#include "Core/FileSystem/FileSystem.h"
#include "Core/Memory/AutomatedMemoryManager.h"
#include "Core/Math/MathFunctions.h"
#include "Core/Types/StaticArray.h"

#include "Managers/Window/WindowManager.h"
#include "Window/Windows/WindowsWindow.h"

#include "Importer/Dynamik/DAI/DAIObject.h"
#include "Importer/Asset/MeshImporter.h"

#include "GameLibrary/Utilities/MeshFactory.h"

#include "Services/RuntimeSystems/AssetRegistry.h"

namespace Dynamik
{
	/* Default constructor */
	DMKEngine::DMKEngine(const DMKGamePackage* gamePackage)
		: pGamePackage(Cast<DMKGamePackage*>(gamePackage))
	{
		/* Initiate the clock */
		_clock.start();

		/* Call the on load function of the game package */
		pGamePackage->onLoad();

		/* Initialize the event pool */
		myEventPool.initialize();

		/* Set the event pool to the player controller */
		myPlayerController.setEventPool(&myEventPool);

		/* Initialize runtime systems */
		_initializeRuntimeSystems();

		/* Initialize singletons */
		DMKErrorManager::logInfo("Welcome to the Dynamik Engine!");
		auto _localPath = DMKFileSystem::getExecutablePath();
		auto _workingDirectory = DMKFileSystem::getWorkingDirectory();
		DMKConfigurationService::openConfigFile(_workingDirectory + "/EngineConfig.ini");

		DMKMeshFactory::setWorkingDirectory(_workingDirectory);
		DMKShaderFactory::setWorkingDirectory(_workingDirectory);

		/* Set the default asset registry path */
		{
			STRING _thisFilePath = __FILE__;
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			DMKAssetRegistry::setDefaultAssetBasePath(_thisFilePath + "\\Assets");
		}

		/* Initialize asset registry */
		DMKAssetRegistry::initializeDefaultAssets();

		/* Create and initialize windows */
		pActiveWindow = _createWindow(1280, 720, "Dynamik Engine");

		/* Issue thread commands */
		_threadManager.issueWindowHandleCommandRT(pActiveWindow);

		_threadManager.issueInitializeCommandRT();
		_threadManager.issueCreateContextCommandRT(DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT, pActiveWindow->createViewport(512, 512, 0, 0));

		/* Call the on init function of the game package */
		pGamePackage->onInit();

		/* Load the level */
		_loadLevel();
	}

	/* Execute the game code */
	void DMKEngine::execute()
	{
		/* Call the on execute function of the game package */
		pGamePackage->onExecute();

		/* Issue renderer commands */
		_threadManager.issueInitializeCameraCommandRT(pCurrentLevel->playerObject->getCameraModule());
		_threadManager.issueInitializeGameWorldCommandRT(pCurrentLevel->pCurrentGameWorld);
		_threadManager.issueInitializeFinalsCommandRT();

		UI64 _itrIndex = 0;
		DMKGameEntity* _entity = nullptr;

#ifdef DMK_DEBUG
		printf("Allocation count: %llu\n", DMKAutomatedMemoryManager::getAllocationCount());

#endif // DMK_DEBUG

		/* Main loop function */
		while (!myEventPool.WindowCloseEvent)
		{
			pGamePackage->onBeginFrame();

			_threadManager.clearCommands();

			pActiveWindow->pollEvents();

			/* Check If The Frame Buffer Was Resized */
			if (myEventPool.FrameBufferResizeEvent)
			{
				auto _extent = pActiveWindow->getWindowExtent();
				myEventPool.FrameBufferResizeEvent = false;

				/* Check if the extent is valid */
				if ((_extent.width <= 0) || (_extent.height <= 0))
				{
					DMK_ERROR("Requested frame buffer extent is Width: " +
						std::to_string(_extent.width) +
						", Height: " + std::to_string(_extent.width) +
						". Since these requested values are invalid the frame buffer will not be resized.");
				}
				else
				{
					pCurrentLevel->playerObject->setAspectRatio(_extent.width / _extent.height);
					_threadManager.issueFrameBufferResizeCommandRT(_extent);
				}
			}

			/* Update entities */
			for (auto entity : pCurrentLevel->pCurrentGameWorld->entities)
			{
				/* Update attachments */
				{
					/* Mesh components */
					for (UI64 index = 0; index < entity->getComponentArray<DMKStaticMeshComponent>()->size(); index++)
					{
						/* Update attachments */
						for (auto attachment : entity->getComponent<DMKStaticMeshComponent>(index)->pAttachments)
							attachment->update();
					}
				}
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

		DMKConfigurationService::writeWindowSize(Cast<F32>(pActiveWindow->windowWidth), Cast<F32>(pActiveWindow->windowHeight));
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