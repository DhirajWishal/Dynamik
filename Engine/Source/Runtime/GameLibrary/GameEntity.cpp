#include "dmkafx.h"
#include "GameEntity.h"

namespace Dynamik
{
	void DMKGameEntity::setupCamera(const POINTER<DMKCameraModule>& cModule)
	{
		for (UI64 index = 0; index < componentManager.getComponentArray<DMKMeshComponent>()->myComponents.size(); index++)
			componentManager.getComponent<DMKMeshComponent>(index)->setCameraModule(cModule);
	}
}
