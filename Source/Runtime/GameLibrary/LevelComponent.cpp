// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "LevelComponent.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{		
	DMKPlayerObject* DMKLevelComponent::createHollowPlayerObject()
	{
		playerObject = StaticAllocator<DMKPlayerObject>::allocate().get();
		return playerObject;
	}
}
