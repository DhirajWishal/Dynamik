#include "DefaultWorld.h"

#include "GameLibrary/Utilities/MeshFactory.h"
#include "Services/RuntimeSystems/AssetRegistry.h"

DefaultWorld::DefaultWorld()
{
	/* Create a basic hollow entity */
	auto entity = createHollowEntity();

	/* Load a basic mesh */
	//entity->addComponent<DMKStaticMeshComponent>(DMKMeshFactory::createDefault(TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx")));
	//entity->getComponent<DMKStaticMeshComponent>(0)->addTexture(TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Diffuse_2K.png"), DMKTextureType::TEXTURE_TYPE_2D);
	//entity->getComponent<DMKStaticMeshComponent>(0)->setPosition({ 0.0f, 0.0f, -5.0f });
	//entity->addComponent<DMKBoundingBoxAttachment>(DMKBoundingBoxAttachment(entity->getComponent<DMKStaticMeshComponent>(0)));

	/* Load another basic mesh */
	entity->addComponent<DMKStaticMeshComponent>(DMKMeshFactory::createDefault(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\venus.fbx")));
	entity->getComponent<DMKStaticMeshComponent>(0)->setPosition({ 0.0f, 0.0f, 5.0f });
	//entity->getComponent<DMKStaticMeshComponent>(1)->addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\tree\\leaves_03.jpg"), DMKTextureType::TEXTURE_TYPE_2D);
	entity->getComponent<DMKStaticMeshComponent>(0)->addMaterial(DMKMaterial::createMetalChromium());
	entity->addComponent<DMKBoundingBoxAttachment>(DMKBoundingBoxAttachment(entity->getComponent<DMKStaticMeshComponent>(1)));
	
	entity->addAttribute(DMKGameEntityAttribute::DMK_GAME_ENTITY_ATTRIBUTE_LIGHTS);
	entity->addAttribute(DMKGameEntityAttribute::DMK_GAME_ENTITY_ATTRIBUTE_CAMERA_PARAMS);

	//entity->addComponent<DMKStaticModel>(DMKMeshFactory::loadStaticModel(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\tree\\Tree.obj")));
	//entity->getComponent<DMKStaticModel>(0)->getMesh(0).addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\tree\\leaves_03.jpg"), DMKTextureType::TEXTURE_TYPE_2D);
	//entity->getComponent<DMKStaticModel>(0)->getMesh(1).addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\tree\\leaves_03.jpg"), DMKTextureType::TEXTURE_TYPE_2D);
	//entity->getComponent<DMKStaticModel>(0)->getMesh(2).addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\tree\\leaves_03.jpg"), DMKTextureType::TEXTURE_TYPE_2D);
	//entity->getComponent<DMKStaticModel>(0)->getMesh(3).addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\tree\\bark_tree.jpg"), DMKTextureType::TEXTURE_TYPE_2D);
	//entity->getComponent<DMKStaticModel>(0)->getMesh(4).addTexture(TEXT("E:\\Projects\\Dynamik Engine\\Game Repository\\assets\\assets\\tree\\ground.jpg"), DMKTextureType::TEXTURE_TYPE_2D);

	/* Load an animated mesh */
	//entity->addComponent<DMKAnimatedMeshComponent>(DMKMeshFactory::loadAnimatedMesh(TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/Skeletal Animation/goblin.dae")));

	/* Initialize Sky Box */
	ARRAY<STRING> texturePaths;
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/right.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/left.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/top.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/bottom.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/front.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/back.jpg");
	//texturePaths.pushBack(TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/abandoned_tank_farm_04_1k.hdr"));
	loadEnvironmentMap(texturePaths);

	DMKGameWorldLightComponent light1;
	light1.colorValue = { 1.0f, 1.0f, 1.0f, 1.0f };
	addLightComponent(light1);
	addLightComponent(light1);
	addLightComponent(light1);
	addLightComponent(light1);
}
