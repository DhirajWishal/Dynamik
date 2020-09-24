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

#include "Renderer/Renderer.h"

/*
 Dynamik Engine Runtime
 This file contains the main engine runtime which are restricted from user access.
*/

DMKGameServer::DMKGameServer()
{
	/* Start the internal clock. */
	clock.start();

	DMKErrorManager::logInfo("Welcome to the Dynamik Engine!");
}

DMKGameServer::~DMKGameServer()
{
	/* End the internal clock. */
	clock.end();
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

	getActiveGameModule()->onInitialize();

	getActiveGameModule()->getCurrentGameWorld()->onMainWindowResize(getCurrentWindowHandle()->getWindowExtent());
}

DMKGameModule* DMKGameServer::getActiveGameModule() const
{
	return pActiveGameModule;
}

DMKRenderer* DMKGameServer::getRenderer() const
{
	return DMKSystemLocator::getSystem<DMKRenderer>();
}

DMKPlayerController* DMKGameServer::getPlayerController() const
{
	return DMKSystemLocator::getSystem<DMKPlayerController>();
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
	/* Initialize the systems required by the game. */
	onInitializeSystems();

	/* Initialize services. */
	onInitializeServices();

	/* Call stage one initializer. */
	onInitializeGame();

	/* Initialize the finals. */
	onInitializeFinal();
}

void DMKGameServer::execute()
{
	while (!DMKSystemLocator::getSystem<DMKEventPool>()->WindowCloseEvent)
	{
		/* Call the stage one update. */
		onBeginUpdate();

		/* Poll events. */
		getCurrentWindowHandle()->pollEvents();

		/* Handle frame buffer resize. */
		if (DMKSystemLocator::getSystem<DMKEventPool>()->FrameBufferResizeEvent)
		{
			auto _extent = getCurrentWindowHandle()->getWindowExtent();
			DMKSystemLocator::getSystem<DMKEventPool>()->FrameBufferResizeEvent = false;

			/* Check if the extent is valid */
			if ((_extent.width > 0) || (_extent.height > 0))
			{
				getActiveGameModule()->getCurrentGameWorld()->onMainWindowResize(_extent);

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

		/* Call the on update game method. */
		onUpdateGame();

		/* Call the on update systems method. */
		onUpdateSystems();

		/* Call the end update method. */
		onEndUpdate();
	}
}

void DMKGameServer::terminate()
{
	/* Call the on terminate game method. */
	onTerminateGame();

	/* Call the on terminate systems method. */
	onTerminateSystems();

	/* Call the on terminate services method. */
	onTerminateServices();

	/* Call the on terminate final method. */
	onTerminateFinal();
}

void DMKGameServer::initializeEventPool()
{
	DMKSystemLocator::createSystem<DMKEventPool>();
	DMKSystemLocator::getSystem<DMKEventPool>()->initialize();
}

void DMKGameServer::initializePlayerController()
{
	DMKSystemLocator::createSystem<DMKPlayerController>();
	DMKSystemLocator::getSystem<DMKPlayerController>()->setEventPool(DMKSystemLocator::getSystem<DMKEventPool>());
}

void DMKGameServer::initializeRenderingEngine(const DMKRendererDescription& description)
{
	DMKSystemLocator::createSystem<DMKRenderer>();
	getRenderer()->initializeThread();

	/* Issue the newly created window handle to the rendering engine. */
	getRenderer()->setWindowHandleCMD(getCurrentWindowHandle());

	/* Submit the initialize command. */
	getRenderer()->initializeCMD(description);
}

void DMKGameServer::terminateRenderingEngine()
{
	getRenderer()->terminateThread();
}

void DMKGameServer::initializeWindowHandle()
{
	/* Create a window handle. */
	pActiveWindowHandle = createWindow(1280, 720, getGameData().gameName);
}

void DMKGameServer::terminateWindowHandle()
{
	getCurrentWindowHandle()->terminate();
	StaticAllocator<DMKWindowHandle>::deallocate(getCurrentWindowHandle(), 0);
}

void DMKGameServer::initializeBasicServices()
{
	auto _localPath = DMKFileSystem::getExecutablePath();
	auto _workingDirectory = DMKFileSystem::getWorkingDirectory();
	DMKConfigurationService::openConfigFile(_workingDirectory + "/EngineConfig.ini");

	DMKMeshFactory::setWorkingDirectory(_workingDirectory);
	DMKShaderFactory::setWorkingDirectory(_workingDirectory);
}

void DMKGameServer::terminateBasicServices()
{
	DMKConfigurationService::writeWindowSize(Cast<F32>(getCurrentWindowHandle()->windowWidth), Cast<F32>(getCurrentWindowHandle()->windowHeight));
	DMKConfigurationService::closeConfigFile();
}

void DMKGameServer::initializeAssetRegistry()
{
	STRING _thisFilePath = __FILE__;
	_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
	_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
	_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
	_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
	DMKAssetRegistry::setDefaultAssetBasePath(_thisFilePath + TEXT("\\Engine\\Assets"));
	DMKAssetRegistry::initializeDefaultAssets();
}

void DMKGameServer::initializeToolsRegistry()
{
	STRING _thisFilePath = __FILE__;
	_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
	_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
	_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
	DMKToolsRegistry::setDefaultToolsBasePath(_thisFilePath + TEXT("\\Dependencies\\ThirdParty\\Binaries"));
	DMKToolsRegistry::initializeDefaultTools();
}

DMKWindowHandle* DMKGameServer::createWindow(UI64 width, UI64 height, const STRING& title)
{
#ifdef DMK_PLATFORM_WINDOWS
	WindowsWindow* pHandle = StaticAllocator<WindowsWindow>::allocateInit(WindowsWindow(title, Cast<I32>(width), Cast<I32>(height)));
	pHandle->initialize();
	pHandle->setEventBoard(DMKSystemLocator::getSystem<DMKEventPool>());
	pHandle->initializeKeyBindings();
	pHandle->setEventCallbacks();

	return pHandle;

#endif // DMK_PLATFORM_WINDOWS

	return nullptr;
}

void DMKGameServer::initializeGameWorld()
{
	if (!getActiveGameModule()->pCurrentGameWorld)
	{
		DMK_WARN("A game world has not been set!");
		return;
	}
}
