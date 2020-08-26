// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_MOON_ENTITY_H
#define _APPLICATION_MOON_ENTITY_H

#include "GameLibrary/Entities/StaticModelEntity.h"
using namespace Dynamik;

class Moon final : public DMKStaticModelEntity {
public:
	Moon() {}
	~Moon() {}

	void initialize();
	void update();
};

#endif // !_APPLICATION_MOON_ENTITY_H
