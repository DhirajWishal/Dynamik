// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_VENUS_MODEL_H
#define _APPLICATION_VENUS_MODEL_H

#include "GameLibrary/GameEntity.h"
#include "Core/Types/StaticArray.h"
using namespace Dynamik;

class VenusModel : public DMKGameEntity {
public:
	VenusModel() {}
	~VenusModel() {}

	virtual void initialize() override final;
	virtual void onUpdate(F32 timeStep) override final;

	struct UniformVS {
		Matrix4F projection = Matrix4F::Identity;
		Matrix4F model = Matrix4F::Identity;
		Matrix4F view = Matrix4F::Identity;
		Vector3F camPos = Vector3F(0.0f);
	} dataVS;

	struct cameraParamsFS {
		StaticArray<Vector4F, 4> lights;
		F32 exposure = 4.5f;
		F32 gamma = 2.2f;
	} camParamFS;
};

#endif // !_APPLICATION_VENUS_MODEL_H
