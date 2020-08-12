// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameServer.h"

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
		while (true)
		{
			/* Call the stage one update. */
			onBeginUpdate();

			/* Call the on update method. */
			onUpdate(1.0f);

			/* Call the end update method. */
			onEndUpdate();
		}
	}

	void DMKGameServer::terminate()
	{
		/* Call the onTerminate method. */
		onTerminate();
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
		pActiveWindowHandle = createWindow(1280, 720, "Dynamik Engine");

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
}
