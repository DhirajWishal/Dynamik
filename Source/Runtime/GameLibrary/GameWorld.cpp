// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameWorld.h"

#include "Utilities/MeshFactory.h"
#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	void DMKGameWorld::initializeEntities(DMKLevelComponent* pCurrentLevel)
	{
		for (auto entity : entities)
		{
			entity->setupCurrentLevel(pCurrentLevel);
			entity->initialize();
		}
	}

	void DMKGameWorld::setCamera(DMKCameraModule* pCameraModule)
	{
		for (auto entity : entities)
			entity->setupCamera(pCameraModule);
	}

	void DMKGameWorld::setEnvironmentMap(DMKEnvironmentMap* pEnvironment)
	{
		pEnvironmentMap = pEnvironment;
	}

	void DMKGameWorld::loadEnvironmentMap(ARRAY<STRING> texturePaths)
	{
		pEnvironmentMap = StaticAllocator<DMKEnvironmentMap>::allocate();
		pEnvironmentMap->skyBox = DMKMeshFactory::createSkyBox(texturePaths);
	}

	void DMKGameWorld::loadEnvironmentMap(STRING texturePath)
	{
	}

	void DMKGameWorld::addLightComponent(DMKGameWorldLightComponent component)
	{
		globalLightComponents.pushBack(component);
	}

	DMKGameEntity* DMKGameWorld::createStaticEntity(const STRING& assetPath)
	{
		return createStaticEntity(assetPath, DMKVertexLayout::createBasic());
	}

	DMKGameEntity* DMKGameWorld::createHollowEntity()
	{
		auto entity = StaticAllocator<DMKGameEntity>::allocate();

		entities.pushBack(entity);
		return entity;
	}

	DMKGameEntity* DMKGameWorld::createStaticEntity(const STRING& assetPath, const DMKVertexLayout& vertexLayout)
	{
		auto meshes = DMKMeshImporter::loadMeshes(assetPath, vertexLayout);
		DMKGameEntity* entity = StaticAllocator<DMKGameEntity>::allocate();

		for (auto mesh : meshes)
		{
			mesh.addShaderModule(DMKShaderFactory::createModule(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Shaders/3D/vert.spv", DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
			mesh.addShaderModule(DMKShaderFactory::createModule(DMKFileSystem::getWorkingDirectory() + "/Runtime/Assets/Shaders/3D/frag.spv", DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

			entity->addComponent<DMKStaticMeshComponent>(mesh);
		}

		entities.pushBack(entity);
		return entity;
	}

	void DMKGameWorld::addEntity(DMKGameEntity* pEntity)
	{
		entities.pushBack(pEntity);
	}

	DMKEnvironmentMap* DMKGameWorld::createHollowEnvironment()
	{
		return StaticAllocator<DMKEnvironmentMap>::allocate();
	}
}