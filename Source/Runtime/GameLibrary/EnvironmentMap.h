// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ENVIRONMENT_MAP_H
#define _DYNAMIK_ENVIRONMENT_MAP_H

#include "Renderer/Entities/StaticModelEntity.h"

namespace Dynamik
{
	/*
	 Dynamik Environment Map
	 This contains all the necessary details of the game environment.

	 Users are allowed to load multiple sky box objects at a time and will be cycled either by using a 
	 user defined method or will use the internal clock to cycle 
	 (allocated time slot per sky box = clock cycle time / total number of sky boxes).
	*/
	class DMK_API DMKEnvironmentMap : public DMKStaticModelEntity {
	public:
		DMKEnvironmentMap() = default;
		virtual ~DMKEnvironmentMap() = default;
	};
}

#endif // !_DYNAMIK_ENVIRONMENT_MAP_H
