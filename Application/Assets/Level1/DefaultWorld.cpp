#include "DefaultWorld.h"

#include "GameLibrary/Utilities/MeshFactory.h"

DefaultWorld::DefaultWorld()
{
	auto entity = createHollowEntity();
	entity->addComponent<DMKMeshComponent>(DMKMeshFactory::createDefault(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx")));
	entity->getComponent<DMKMeshComponent>(0)->addTexture(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Diffuse_2K.png"), DMKTextureType::DMK_TEXTURE_TYPE_2D);
	entity->getComponent<DMKMeshComponent>(0)->translate(MAT4(1.0f), { 0.0f, 0.0f, -5.0f });

	/* Initialize Sky Box */
	ARRAY<STRING> texturePaths;
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/right.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/left.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/top.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/bottom.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/front.jpg");
	texturePaths.pushBack(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Textures/SkyBox/back.jpg");
	loadEnvironmentMap(texturePaths);
}
