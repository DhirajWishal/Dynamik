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
    /* Main singleton implementation */
    DMK_CLASS_SINGLETON_IMPL(DMKEngine);

    /* Default constructor */
    DMKEngine::DMKEngine()
    {
        DMKClock::start();

        DAIObject _myFile("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\Skybox");
        _myFile.load();
        auto modelPaths = _myFile.meshes;

        auto file = DMKMeshImporter::loadMesh("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\Skybox\\SkySphere.obj", DMKVertexBufferDescriptor());
    }
    
    /* Default destructor */
    DMKEngine::~DMKEngine()
    {
        DMKWindowManager::terminateAll();

        DMKClock::end();
    }

    void DMKEngine::execute()
    {
        while (true) 
        {
            DMKWindowManager::pollEvents();
            DMKWindowManager::clean();
        }
    }
    
    /* Create the Dynamik Engine instance. */
    void DMKEngine::createInstance()
    {
        DMKErrorManager::logInfo("Welcome to the Dynamik Engine!");
        DMKWindowManager::createWindow(1280, 720);

        auto _localPath = DMKFileSystem::getExecutablePath();
    }
}