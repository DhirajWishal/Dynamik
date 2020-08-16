// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_PLAYER_H
#define _APPLICATION_PLAYER_H

#include "GameLibrary/Entities/PlayerEntity.h"
using namespace Dynamik;

class Player final : public DMKPlayerEntity {
public:
	Player() {}
	~Player() {}

	virtual void onInitializePlayer() override final;
};

#endif // !_APPLICATION_PLAYER_H
