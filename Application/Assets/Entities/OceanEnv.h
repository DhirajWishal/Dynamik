// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_OCEAN_ENVIRONMENT_H
#define _APPLICATION_OCEAN_ENVIRONMENT_H

#include "GameLibrary/Entities/EnvironmentEntity.h"
using namespace Dynamik;

class OceanEnv final : public DMKEnvironmentEntity {
public:
	OceanEnv() {}
	~OceanEnv() {}

	virtual void onInitializeEnvironment() override final;
};

#endif // !_APPLICATION_OCEAN_ENVIRONMENT_H
