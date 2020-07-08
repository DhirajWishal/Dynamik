// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_IMPORTER_H
#define _DYNAMIK_ANIMATION_IMPORTER_H

#include "Animation/AnimatedMeshComponent.h"

namespace Dynamik
{
	/*
	 Dynamik Animation Importer
	*/
	class DMK_API DMKAnimationImporter {
	public:
		DMKAnimationImporter() {}
		~DMKAnimationImporter() {}

		/*
		 Load animation from an asset file.
		*/
		static DMKAnimatedMeshComponent loadAnimation(const STRING& path);
	};
}

#endif // !_DYNAMIK_ANIMATION_IMPORTER_H
