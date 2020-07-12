// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ApplicationPackage.h"

ApplicationPackage::ApplicationPackage()
{
	gameName = TEXT("Application example");
	gameVersion = 0x0001;
	gameAssetBasePath = TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets");

	myFirstLevel = Level1();
}

void ApplicationPackage::onLoad()
{
	levels.pushBack(&myFirstLevel);
}

void ApplicationPackage::onInit()
{
	DMKErrorManager::logInfo(TEXT("Entered onInit function!"));
}

void ApplicationPackage::onLevelLoad(UI64 levelIndex)
{
	DMKErrorManager::logInfo(TEXT("Loading a new level! ") + std::to_string(levelIndex));
}
