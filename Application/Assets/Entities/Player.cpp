// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Player.h"

void Player::onInitializePlayer()
{
	cameraModule = StaticAllocator<DMKCameraModule>::allocate();

	this->setPosition({ 0.0f, 0.0f, 0.0f });
	this->setCameraPosition({ 0.0f, 0.0f, 0.0f });
	this->setCameraAndWorldUp(VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f));
	this->getCameraModule()->setExposure(1.0f);
	this->getCameraModule()->setGamma(1.0f);
}
