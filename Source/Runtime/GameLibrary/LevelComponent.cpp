// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "LevelComponent.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	void DMKLevelComponent::initializeCameraModule()
	{
		for (auto _entity : entities)
			_entity->setupCamera(playerObject->getCameraModule());
	}

	DMKGameEntity* DMKLevelComponent::createHollowEntity()
	{
		auto entity = StaticAllocator<DMKGameEntity>::allocate();

		entities.pushBack(entity);
		return entity;
	}

	DMKGameEntity* DMKLevelComponent::createStaticEntity(const STRING& assetPath)
	{
		return createStaticEntity(assetPath, DMKVertexLayout::createBasic());
	}

	DMKGameEntity* DMKLevelComponent::createStaticEntity(const STRING& assetPath, const DMKVertexLayout& vertexLayout)
	{
		auto meshes = DMKMeshImporter::loadMeshes(assetPath, vertexLayout);
		DMKGameEntity* entity = StaticAllocator<DMKGameEntity>::allocate();

		for (auto mesh : meshes)
			entity->addComponent<DMKMeshComponent>(mesh);

		entities.pushBack(entity);
		return entity;
	}
	
	void DMKLevelComponent::addEntity(DMKGameEntity* pEntity)
	{
		entities.pushBack(pEntity);
	}
	
	DMKPlayerObject* DMKLevelComponent::createHollowPlayerObject()
	{
		playerObject = StaticAllocator<DMKPlayerObject>::allocate().get();
		return playerObject;
	}
}
