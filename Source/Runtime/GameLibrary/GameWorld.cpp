// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "GameWorld.h"

#include "Utilities/MeshFactory.h"
#include "Importer/Asset/MeshImporter.h"
#include "Importer/Asset/AnimationImporter.h"

namespace Dynamik
{
	void DMKGameWorld::initializeEntities()
	{
		for (auto entity : entities)
			entity->initialize();
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

	void DMKGameWorld::addEntity(DMKGameEntity* pEntity)
	{
		entities.pushBack(pEntity);
	}

	DMKGameEntity* DMKGameWorld::createStaticEntity(const STRING& assetPath)
	{
		return createStaticEntity(assetPath, DMKVertexLayout::createBasic());
	}

	DMKGameEntity* DMKGameWorld::createHollowEntity()
	{
		auto entity = StaticAllocator<DMKGameEntity>::allocate();

		addEntity(entity);
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

			entity->addComponent<DMKMeshComponent>(mesh);
		}

		addEntity(entity);
		return entity;
	}

	DMKGameEntity* DMKGameWorld::createAnimatedEntity(const STRING& assetPath)
	{
		return createAnimatedEntity(assetPath, DMKVertexLayout::createAnimated());
	}

	DMKGameEntity* DMKGameWorld::createAnimatedEntity(const STRING& assetPath, const DMKVertexLayout& vertexLayout)
	{
		auto animation = DMKAnimationImporter::loadAnimation(assetPath, vertexLayout);
		DMKGameEntity* pEntity = StaticAllocator<DMKGameEntity>::allocate();

		animation.skinnedMesh.addShaderModule(DMKShaderFactory::createAnimated(DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX));
		animation.skinnedMesh.addShaderModule(DMKShaderFactory::createAnimated(DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT));
		pEntity->addComponent<DMKAnimatedMeshComponent>(animation);

		addEntity(pEntity);
		return pEntity;
	}

	DMKEnvironmentMap* DMKGameWorld::createHollowEnvironment()
	{
		return StaticAllocator<DMKEnvironmentMap>::allocate();
	}
}