// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ApplicationServer.h"
#include "Assets/Modules/Module00/Module00.h"

#include "Core/Error/ErrorManager.h"

void ApplicationServer::onInitializeSystems()
{
	/* Initialize the event pool. */
	initializeEventPool();

	/* Initialize the player controller. */
	initializePlayerController();

	/* Initialize the window. */
	initializeWindowHandle();

	/* Initialize the rendering engine. */
	initializeRenderingEngine();

	/* Create the rendering context. */
	getRenderer()->createContextCMD(getCurrentWindowHandle()->createViewport(512, 512, 0, 0), DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT);
}

void ApplicationServer::onInitializeServices()
{
	/* Initialize the basic services. */
	initializeBasicServices();

	/* Initialize the asset registry. */
	initializeAssetRegistry();

	/* Initialize the tools registry. */
	initializeToolsRegistry();
}

void ApplicationServer::onInitializeGame()
{
	loadGameModule(StaticAllocator<Module00>::allocate());
}

void ApplicationServer::onInitializeFinal()
{
	/* Initialize the renderer finals. */
	getRenderer()->initializeFinalsCMD();
}

void ApplicationServer::onBeginUpdate()
{
	/* Poll events from the current window handle. */
	getCurrentWindowHandle()->pollEvents();
}

void ApplicationServer::onUpdateGame()
{
	/* Update the game module. */
	getActiveGameModule()->onUpdate(1.0f);

	/* Update the entities of the current module. */
	getActiveGameModule()->updateEntities(1.0f);
}

void ApplicationServer::onUpdateSystems()
{
	/* Execute the player controls. */
	getPlayerController()->executeAll();

	/* Update the rendering engine. */
	getRenderer()->update();
}

void ApplicationServer::onEndUpdate()
{
	/* Clean the handled events from the window handle. */
	getCurrentWindowHandle()->clean();
}

void ApplicationServer::onTerminateGame()
{
	DMK_INFO("Game is terminated!");
}

void ApplicationServer::onTerminateSystems()
{
	/* Terminate the rendering engine. */
	terminateRenderingEngine();

	/* Terminate the window handle. */
	terminateWindowHandle();
}

void ApplicationServer::onTerminateServices()
{
	/* Terminate the basic services. */
	terminateBasicServices();
}

void ApplicationServer::onTerminateFinal()
{
}

DMK_SETUP_SERVER(ApplicationServer)