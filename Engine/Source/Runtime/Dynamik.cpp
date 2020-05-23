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

        DAIObject _myFile("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\Skybox");
        _myFile.load();
        auto modelPaths = _myFile.meshes;

        auto file = DMKMeshImporter::loadMesh("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\Skybox\\SkySphere.obj", DMKVertexBufferDescriptor());
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
        _windowManager.createWindow(1280, 720, descriptor.applicationName);

        auto _localPath = DMKFileSystem::getExecutablePath();
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
        while (true)
        {
            _windowManager.pollEvents();
            _windowManager.clean();
        }
    }
}