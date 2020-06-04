/*
 This file contains all the definitions of the Dynamik Engine interface.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "dmkafx.h"
#include "Dynamik.h"

#include "Error/ErrorManager.h"
#include "Core/Utilities/Clock.h"
#include "Core/FileSystem/FileSystem.h"

#include "Managers/Window/WindowManager.h"

#include "Importer/Dynamik/DAI/DAIObject.h"
#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
    /* Default constructor */
    DMKEngine::DMKEngine()
    {
        _clock.start();
        _threadManager.initializeBasicThreads();
    }
    
    /* Default destructor */
    DMKEngine::~DMKEngine()
    {
        _windowManager.terminateAll();
        _clock.end();
    }
    
    /* Create the Dynamik Engine  */
    void DMKEngine::createInstance(DMKEngineInstanceDescriptor descriptor)
    {
        DMKErrorManager::logInfo("Welcome to the Dynamik Engine!");
        auto _localPath = DMKFileSystem::getExecutablePath();
    }

    void DMKEngine::createWindow(STRING title, UI32 width, UI32 height)
    {
        UI32 windowID = _windowManager.createWindow(width, height, title);
        _threadManager.issueWindowHandleCommandRT(_windowManager.getWindowHandle(windowID));
        _threadManager.issueCreateContextCommandRT(DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT, _windowManager.createViewport(windowID, 512, 512, 0, 0));
    }

    void DMKEngine::setGamePackage(const DMKGamePackage& package)
    {
    }

    void DMKEngine::initializeComponents()
    {
        _threadManager.issueInitializeCommandRT();
    }

    void DMKEngine::setLevels(ARRAY<POINTER<DMKLevelComponent>> levelComponents)
    {
        for (auto _level : levelComponents)
        {
            _gameComponentManager.addLevel(_level);
        }
    }

    /* Execute the game code */
    void DMKEngine::execute()
    {
        _threadManager.issueInitializeObjectCommandRT();
        _threadManager.issueInitializeFinalsCommandRT();

        while (true)
        {
            _threadManager.clearCommands();

            _windowManager.pollEvents();
            _windowManager.clean();
        }
    }
}