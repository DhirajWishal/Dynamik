// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ApplicationPackage.h"

ApplicationPackage::ApplicationPackage()
{
	gameName = DMK_TEXT("Application example");
	gameVersion = 0x0001;
	gameAssetBasePath = DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets");

	myFirstLevel = Level1();
}

void ApplicationPackage::onLoad()
{
	levels.pushBack(&myFirstLevel);
}

void ApplicationPackage::onInit()
{
	DMKErrorManager::logInfo(DMK_TEXT("Entered onInit function!"));
}

void ApplicationPackage::onLevelLoad(UI64 levelIndex)
{
	DMKErrorManager::logInfo(DMK_TEXT("Loading a new level! ") + std::to_string(levelIndex));
}
