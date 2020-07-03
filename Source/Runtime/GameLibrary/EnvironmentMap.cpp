// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "EnvironmentMap.h"

#include "Utilities/MeshFactory.h"

namespace Dynamik
{
	void DMKEnvironmentMap::setSkyBox(const DMKMeshComponent& component)
	{
		skyBox = component;
	}
}