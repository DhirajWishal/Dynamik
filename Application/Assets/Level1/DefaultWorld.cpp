// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "DefaultWorld.h"
#include "Entities/VenusModel.h"
#include "SkySphere.h"
#include "Entities/CerberusModel.h"
#include "Entities/TestScene.h"


#include "GameLibrary/Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "GameLibrary/Entities/StaticEntity.h"

void DefaultWorld::initialize()
{
	//auto entity1 = createUserEntity<VenusModel>();
	//auto cerberus = createUserEntity<CerberusModel>();
	auto estScene = createUserEntity<TestScene>();

	//auto entity1 = createUserEntity<DMKStaticEntity>();
	//entity1->loadAsset(
	//	TEXT("E:\\Dynamik\\Game Repository\\assets\\assets\\moon\\Moon 2K.fbx"),
	//	{ DMKTextureFactory::create(DMKTextureType::TEXTURE_TYPE_2D, TEXT("E:\\Dynamik\\Game Repository\\assets\\assets\\moon\\Diffuse_2K.png")) }
	//);

	/* Initialize Sky Box */
	createUserEnvironment<SkySphere>(SkySphere());

	DMKGameWorldLightComponent light1;
	light1.colorValue = { 1.0f, 1.0f, 1.0f, 1.0f };
	addLightComponent(light1);
	addLightComponent(light1);
	addLightComponent(light1);
	addLightComponent(light1);
}
