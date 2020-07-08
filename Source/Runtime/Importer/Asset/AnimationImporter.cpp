// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimationImporter.h"

#include "Wrappers/AssimpWrapper.h"

namespace Dynamik
{
	DMKAnimatedMeshComponent DMKAnimationImporter::loadAnimation(const STRING& path, const DMKVertexLayout& vertexLayout, const UI32& nodesPerVertex)
	{
		AssimpWrapper wrapper;
		return wrapper.loadAnimatedModel(path, vertexLayout, nodesPerVertex);
	}
}
