// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameWorld.h"

#include "Utilities/MeshFactory.h"
#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	void DMKGameWorld::addLightComponent(DMKGameWorldLightComponent component)
	{
		globalLightComponents.pushBack(component);
	}
}