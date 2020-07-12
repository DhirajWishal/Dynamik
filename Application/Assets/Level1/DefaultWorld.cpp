#include "DefaultWorld.h"

#include "GameLibrary/Utilities/MeshFactory.h"

DefaultWorld::DefaultWorld()
{
	auto entity = createHollowEntity();
	entity->addComponent<DMKStaticMeshComponent>(DMKMeshFactory::createDefault(TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx")));
	entity->getComponent<DMKStaticMeshComponent>(0)->addTexture(TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Diffuse_2K.png"), DMKTextureType::TEXTURE_TYPE_2D);
	entity->getComponent<DMKStaticMeshComponent>(0)->translate(MAT4(1.0f), { 0.0f, 0.0f, -5.0f });

	entity->addComponent<DMKStaticMeshComponent>(DMKMeshFactory::createDefault(TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx")));
	entity->getComponent<DMKStaticMeshComponent>(1)->translate(MAT4(1.0f), { 0.0f, 0.0f, 5.0f });
	entity->getComponent<DMKStaticMeshComponent>(1)->addMaterial(DMKMaterial::createMetalNickel());
	entity->getComponent<DMKStaticMeshComponent>(1)->shaderModules.clear();
	entity->getComponent<DMKStaticMeshComponent>(1)->addShaderModule(DMKShaderFactory::createModule(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Shaders/PBR/Tests/vert.spv", DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
	entity->getComponent<DMKStaticMeshComponent>(1)->addShaderModule(DMKShaderFactory::createModule(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Shaders/PBR/Tests/frag.spv", DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

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
