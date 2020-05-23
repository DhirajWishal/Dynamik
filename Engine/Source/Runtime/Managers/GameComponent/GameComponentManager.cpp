#include "dmkafx.h"
#include "GameComponentManager.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	/*
	 Worker function for loading multiple meshes in another thread.
	*/
	void _meshLoadingWorker(POINTER<DMKSceneComponent> scene)
	{

	}

	void DMKGameComponentManager::addLevel(POINTER<DMKLevelComponent> levelComponent)
	{
		myLevelStore.pushBack(levelComponent);
	}
	
	void DMKGameComponentManager::loadLevel(UI32 levelIndex)
	{
		auto _level = myLevelStore[levelIndex];

		for (auto _scene : _level->mySceneComponents)
		{

		}
	}
	
	void DMKGameComponentManager::unloadLevel(UI32 levelIndex)
	{
	}
}