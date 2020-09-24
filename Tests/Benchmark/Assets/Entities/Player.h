// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_PLAYER_H
#define _APPLICATION_PLAYER_H

#include "GameLibrary/Entities/PlayerEntity.h"

class Player final : public DMKPlayerEntity {
public:
	Player() {}
	~Player() {}

	virtual void onInitializePlayer() override final;
	virtual void setupPlayerControls(DMKPlayerController* pPlayerController) override final;

	virtual void onMoveForward() override final;
	virtual void onMoveBackward() override final;
	virtual void onMoveLeft() override final;
	virtual void onMoveRight() override final;
};

#endif // !_APPLICATION_PLAYER_H
