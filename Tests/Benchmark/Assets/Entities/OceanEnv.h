// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_OCEAN_ENVIRONMENT_H
#define _APPLICATION_OCEAN_ENVIRONMENT_H

#include "GameLibrary/Entities/EnvironmentEntity.h"
#include "GameLibrary/Camera/CameraModule.h"
#include "Core/Types/StaticArray.h"

class OceanEnv final : public DMKEnvironmentEntity {
public:
	OceanEnv() {}
	~OceanEnv() {}

	void setCameraModule(DMKCameraModule* pCameraModule);

	virtual void onInitializeEnvironment() override final;
	virtual void onUpdateEnvironment() override final;

	struct UniformFS {
		F32 exposure = 4.5f;
		F32 gamma = 2.2f;
	} fsUBO;

	DMKCameraModule* pCameraModule = nullptr;
};

#endif // !_APPLICATION_OCEAN_ENVIRONMENT_H
