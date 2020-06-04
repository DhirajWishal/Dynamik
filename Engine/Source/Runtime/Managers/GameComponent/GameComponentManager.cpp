#include "dmkafx.h"
#include "GameComponentManager.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	void DMKGameComponentManager::setGamePackage(const DMKGamePackage& package)
	{
		myCurrentPackage = package;
	}

	void DMKGameComponentManager::loadLevel(UI32 levelIndex)
	{
	}
	
	void DMKGameComponentManager::unloadLevel(UI32 levelIndex)
	{
	}
}