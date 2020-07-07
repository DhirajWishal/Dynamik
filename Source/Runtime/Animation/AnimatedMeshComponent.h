// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATED_MESH_COMPONENT_H
#define _DYNAMIK_ANIMATED_MESH_COMPONENT_H

#include "Objects/Animation.h"

namespace Dynamik
{
	/*
	 Dynamik Animated Mesh Component

	 This component stores all the relevant data to store an animation.
	 This component contains,
	 - Skinned Mesh (DMKMeshComponent)
	 - Bone Mesh (DMKAnimation)
	*/
	class DMK_API DMKAnimatedMeshComponent {
	public:
		DMKAnimatedMeshComponent() {}
		~DMKAnimatedMeshComponent() {}
	};
}

#endif // !_DYNAMIK_ANIMATED_MESH_COMPONENT_H
