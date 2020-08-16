// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameModule.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	DMKGameModule::DMKGameModule()
	{
		pCurrentGameWorld = nullptr;
	}

	void DMKGameModule::updateEntities(F32 timeStep)
	{
		pCurrentGameWorld->onUpdate(timeStep);
	}
}
