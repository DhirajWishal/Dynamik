// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_LEVEL_1_H
#define _DYNAMIK_LEVEL_1_H

#include "GameLibrary/LevelComponent.h"
#include "Entities/PlayerMoon.h"
using namespace Dynamik;

class Level1 : public DMKLevelComponent {
public:
	Level1() {}
	~Level1() {}

	void onLoad() override;
	virtual void onUpdate(const DMKEventPool* pEventPool) override final;
	virtual void setupPlayerControls(DMKPlayerController* pController) override final;

	virtual void onPlayerMoveForward() override final;
	virtual void onPlayerMoveBackward() override final;
	virtual void onPlayerMoveLeft() override final;
	virtual void onPlayerMoveRight() override final;

private:
	F32 movementBias = 0.1f;
};

#endif // !_DYNAMIK_LEVEL_1_H
