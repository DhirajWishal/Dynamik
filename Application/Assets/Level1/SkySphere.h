// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_SKY_SPHERE_H
#define _APPLICATION_SKY_SPHERE_H

#include "GameLibrary/EnvironmentMap.h"
#include "Core/Types/StaticArray.h"
using namespace Dynamik;

class SkySphere : public DMKEnvironmentMap {
public:
	SkySphere();
	~SkySphere() {}

	virtual void onUpdate(F32 timeStep) override final;

	struct UniformFS {
		StaticArray<Vector4F, 4> lights;
		F32 exposure;
		F32 gamma;
	} fsUBO;
};

#endif // !_APPLICATION_SKY_SPHERE_H
