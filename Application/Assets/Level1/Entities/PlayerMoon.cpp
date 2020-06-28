// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "PlayerMoon.h"
#include "GameLibrary/Utilities/MeshFactory.h"
#include "Importer/Asset/MeshImporter.h"

void PlayerMoon::initialize()
{
	componentManager.addComponent<DMKMeshComponent>(DMKMeshFactory::createBasicTriangle());
}
