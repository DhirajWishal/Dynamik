// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameModule.h"

#include "Importer/Asset/MeshImporter.h"

DMKGameModule::DMKGameModule()
{
	pCurrentGameWorld = nullptr;
}

void DMKGameModule::updateEntities(F32 timeStep)
{
	if (pCurrentGameWorld)
		pCurrentGameWorld->onUpdate(timeStep);
}
