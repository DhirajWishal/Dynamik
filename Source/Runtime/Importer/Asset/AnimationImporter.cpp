// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimationImporter.h"

#include "Wrappers/AssimpWrapper.h"

namespace Dynamik
{
	DMKAnimatedModelEntity DMKAnimationImporter::loadAnimation(const STRING& path)
	{
		AssimpWrapper _wrapper;
		return _wrapper.loadAnimatedModelEntity(path, DMKVertexLayout::createAnimated());
	}
}
