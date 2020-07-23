// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "DefaultWorld.h"
#include "Entities/VenusModel.h"
#include "SkySphere.h"

#include "GameLibrary/Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"

DefaultWorld::DefaultWorld()
{
	auto entity = createUserEntity<VenusModel>();

	/* Initialize Sky Box */
	//ARRAY<STRING> texturePaths;
	//texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/right.jpg");
	//texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/left.jpg");
	//texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/top.jpg");
	//texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/bottom.jpg");
	//texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/front.jpg");
	//texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/back.jpg");
	//texturePaths.pushBack(TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/abandoned_tank_farm_04_1k.hdr"));
	//loadEnvironmentMap(texturePaths);
	createUserEnvironment<SkySphere>(SkySphere());

	DMKGameWorldLightComponent light1;
	light1.colorValue = { 1.0f, 1.0f, 1.0f, 1.0f };
	addLightComponent(light1);
	addLightComponent(light1);
	addLightComponent(light1);
	addLightComponent(light1);
}
