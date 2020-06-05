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
    DMKEngine::DMKEngine(const DMKEngineInstanceDescriptor& instanceDescriptor, const POINTER<DMKGamePackage>& gamePackage)
        : _instanceDescription(instanceDescriptor), _gamePackage(gamePackage)
    {
        _clock.start();
        _gamePackage->onLoad();

        _initializeRuntimeSystems();

        DMKErrorManager::logInfo("Welcome to the Dynamik Engine!");
        auto _localPath = DMKFileSystem::getExecutablePath();

        UI32 windowID = _windowManager.createWindow(_instanceDescription.windowDescription.width, _instanceDescription.windowDescription.height, _instanceDescription.windowDescription.title);
        _threadManager.issueWindowHandleCommandRT(_windowManager.getWindowHandle(windowID));

        _threadManager.issueInitializeCommandRT();
        _threadManager.issueCreateContextCommandRT(DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT, _windowManager.createViewport(windowID, 512, 512, 0, 0));
    
        _gamePackage->onInit();
    }

    /* Execute the game code */
    void DMKEngine::execute()
    {

        _gamePackage->onExecute();
        _threadManager.issueInitializeObjectCommandRT();
        _threadManager.issueInitializeFinalsCommandRT();

        while (true)
        {
            _gamePackage->onBeginFrame();

            _threadManager.clearCommands();

            _windowManager.pollEvents();
            _windowManager.clean();

            _gamePackage->onEndFrame();
        }
    }

    /* Default destructor */
    DMKEngine::~DMKEngine()
    {
        _gamePackage->onExit();

        _windowManager.terminateAll();
        _clock.end();
    }

    void DMKEngine::_initializeRuntimeSystems()
    {
        _threadManager.initializeBasicThreads();
    }
    
    void DMKEngine::_loadLevel()
    {
        _gamePackage->onLevelLoad(_nextLevelIndex);
        _currentLevel = _gamePackage->levels[_nextLevelIndex++];
    }
}