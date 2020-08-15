// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameServer.h"

#include "Core/Error/ErrorManager.h"
#include "Core/FileSystem/FileSystem.h"
#include "Core/Math/MathFunctions.h"
#include "Core/Memory/AutomatedMemoryManager.h"
#include "Core/Types/StaticArray.h"
#include "Core/Utilities/Clock.h"
#include "Core/Utilities/ShaderFactory.h"

#include "Managers/Window/WindowManager.h"

#include "Window/Windows/WindowsWindow.h"

#include "Importer/Dynamik/DAI/DAIObject.h"
#include "Importer/Asset/MeshImporter.h"

#include "GameLibrary/Utilities/MeshFactory.h"

#include "Services/SystemLocator.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Services/RuntimeSystems/ToolsRegistry.h"

#include "Importer/Asset/ImageImporter.h"

/*
 Dynamik Engine Runtime
 This file contains the main engine runtime which are restricted from user access.
*/

namespace Dynamik
{
	DMKGameServer::DMKGameServer()
	{
		DMKErrorManager::logInfo("Welcome to the Dynamik Engine!");

		/* Initialize the engine. */
		initialize();

		/* Execute the engine. */
		execute();
	}

	DMKGameServer::~DMKGameServer()
	{
		/* Terminate the engine. */
		terminate();
	}

	void DMKGameServer::setGameData(const DMKGameData& gameData)
	{
		this->gameData = gameData;
	}

	DMKGameData& DMKGameServer::getGameData() const
	{
		return Cast<DMKGameData&>(gameData);
	}

	void DMKGameServer::loadGameModule(DMKGameModule* pModule)
	{
		this->pActiveGameModule = pModule;
		this->pActiveGameModule->setGameServer(this);

		getActiveGameModule()->onLoad();

		initializeGameWorld();

		getActiveGameModule()->initializeComponents();

		getActiveGameModule()->setupPlayerControls(&playerController);
		getActiveGameModule()->playerObject->setCameraViewPort(getCurrentWindowHandle()->getWindowExtent());
	}

	DMKGameModule* DMKGameServer::getActiveGameModule() const
	{
		return pActiveGameModule;
	}

	DMKRenderer* DMKGameServer::getRenderer() const
	{
		return DMKSystemLocator::getSystem<DMKRenderer>();
	}

	DMKClock& DMKGameServer::getClock() const
	{
		return Cast<DMKClock&>(clock);
	}

	DMKWindowHandle* DMKGameServer::getCurrentWindowHandle() const
	{
		return pActiveWindowHandle;
	}

	void DMKGameServer::initialize()
	{
		/* Initialize the runtime systems. */
		initializeRuntimeSystems();

		/* Call stage one initializer. */
		onInitializeStageOne();

		/* Initialize the event pool. */
		eventPool.initialize();

		/* Initialize services. */
		initializeServices();

		/* Call stage two initializer. */
		onInitializeStageTwo();

		/* Initialize window handle */
		initializeWindowHandle();

		/* Issue final commands */
		getRenderer()->initializeCMD();
		getRenderer()->createContextCMD(pActiveWindowHandle->createViewport(512, 512, 0, 0), DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT);

		/* Call the stage three initializer */
		onInitializeStageThree();
	}

	void DMKGameServer::execute()
	{
		/* Submit data */
		submitGameWorldData();

		/* Initialize the finals */
		getRenderer()->initializeCameraModuleCMD(getActiveGameModule()->getCameraModule());
		getRenderer()->initializeGameWorldCMD(getActiveGameModule()->pCurrentGameWorld);
		//getRenderer()->initializeEntitiesCMD(getActiveGameModule()->pEntities);
		getRenderer()->initializeFinalsCMD();

		/* Let the game module submit its data to the required systems. */
		getActiveGameModule()->onSubmitDataToSystems();

		while (!eventPool.WindowCloseEvent)
		{
			/* Call the stage one update. */
			onBeginUpdate();

			/* Poll events. */
			getCurrentWindowHandle()->pollEvents();

			if (eventPool.FrameBufferResizeEvent)
			{
				auto _extent = getCurrentWindowHandle()->getWindowExtent();
				eventPool.FrameBufferResizeEvent = false;

				/* Check if the extent is valid */
				if ((_extent.width > 0) || (_extent.height > 0))
				{
					getActiveGameModule()->playerObject->setAspectRatio(_extent.width / _extent.height);
					getActiveGameModule()->playerObject->setCameraViewPort(_extent);

					getRenderer()->setFrameBufferResizeCMD(_extent);
				}
				else
				{
					DMK_ERROR("Requested frame buffer extent is Width: " +
						std::to_string(_extent.width) +
						", Height: " + std::to_string(_extent.width) +
						". Since these requested values are invalid the frame buffer will not be resized.");
				}
			}

			/* Call the on update method. */
			onUpdate(1.0f);

			/* Update entities */
			getActiveGameModule()->updateEntities(1.0f);

			/* Update the rendering engine */
			getRenderer()->issueRawCommand(RendererInstruction::RENDERER_INSTRUCTION_DRAW_UPDATE);

			/* Clear all events */
			getCurrentWindowHandle()->clean();

			/* Call the end update method. */
			onEndUpdate();
		}
	}

	void DMKGameServer::terminate()
	{
		/* Call the onTerminate method. */
		onTerminate();

		/* Terminate the rendering engine */
		getRenderer()->terminateThread();

		DMKConfigurationService::writeWindowSize(Cast<F32>(getCurrentWindowHandle()->windowWidth), Cast<F32>(getCurrentWindowHandle()->windowHeight));
		getCurrentWindowHandle()->terminate();

		DMKConfigurationService::closeConfigFile();
		clock.end();
	}

	void DMKGameServer::initializeRuntimeSystems()
	{
		/* Initialize the renderer */
		{
			DMKSystemLocator::createSystem<DMKRenderer>();
			getRenderer()->initializeThread();
		}
	}

	void DMKGameServer::initializeServices()
	{
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
			DMKAssetRegistry::setDefaultAssetBasePath(_thisFilePath + TEXT("\\Assets"));
			DMKAssetRegistry::initializeDefaultAssets();
		}

		/* Set the default tool registry path */
		{
			STRING _thisFilePath = __FILE__;
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			DMKToolsRegistry::setDefaultToolsBasePath(_thisFilePath + TEXT("\\Dependencies\\ThirdParty\\Binaries"));
			DMKToolsRegistry::initializeDefaultTools();
		}
	}

	void DMKGameServer::initializeWindowHandle()
	{
		/* Create a window handle. */
		pActiveWindowHandle = createWindow(1280, 720, getGameData().gameName);

		/* Issue the newly created window handle to the required systems. */
		getRenderer()->setWindowHandleCMD(pActiveWindowHandle);
	}

	DMKWindowHandle* DMKGameServer::createWindow(UI64 width, UI64 height, const STRING& title)
	{
#ifdef DMK_PLATFORM_WINDOWS
		DMKWindowHandle* pHandle = StaticAllocator<WindowsWindow>::allocateInit(WindowsWindow(title, width, height));
		pHandle->initialize();
		pHandle->setEventBoard(&eventPool);
		pHandle->initializeKeyBindings();
		pHandle->setEventCallbacks();

		return pHandle;

#endif // DMK_PLATFORM_WINDOWS

		return nullptr;
	}

	void DMKGameServer::submitGameWorldData()
	{
	}

	void DMKGameServer::initializeGameWorld()
	{
		if (!getActiveGameModule()->pCurrentGameWorld)
		{
			DMK_WARN("A game world has not been set!");
			return;
		}
		getActiveGameModule()->pCurrentGameWorld->setPlayerObject(getActiveGameModule()->playerObject);
		getActiveGameModule()->pCurrentGameWorld->initialize();
		getActiveGameModule()->pCurrentGameWorld->onSubmitData();
	}
}